import {execFileSync} from "node:child_process"
import {mkdirSync, readFileSync, writeFileSync} from "node:fs"
import {dirname, join} from "node:path"
import {fileURLToPath} from "node:url"

type Source = {
  filepath: string
  line: number
  col: number
}

type ApiItem = {
  kind: string
  name: string
  signature: string
  docstrings: string[]
  source: Source
}

type Documentation = {
  items: ApiItem[]
}

type PackageJson = {
  name: string
  version: string
  repository: string | {url: string}
}

const root = join(dirname(fileURLToPath(import.meta.url)), "..")
const outputDirectory = join(root, "docs-site")
const sourceFile = "src/TinyColor.resi"
const tools = join(root, "node_modules/rescript/cli/rescript-tools.js")
const packageJson = JSON.parse(
  readFileSync(join(root, "package.json"), "utf8"),
) as PackageJson

const extracted = execFileSync(process.execPath, [tools, "doc", sourceFile], {
  cwd: root,
  encoding: "utf8",
})

if (extracted.trim() === "") {
  throw new Error(`No documentation was extracted from ${sourceFile}`)
}

const documentation = JSON.parse(extracted) as Documentation
const apiItems = documentation.items

if (apiItems.length === 0) {
  throw new Error(`No public API entries were extracted from ${sourceFile}`)
}

const formatKind = (kind: string): string =>
  `${kind.replace(/([a-z])([A-Z])/g, "$1 $2").replace(/^./, first => first.toUpperCase())}s`

const grouped = new Map<string, ApiItem[]>()
for (const item of apiItems) {
  const category = formatKind(item.kind)
  grouped.set(category, [...(grouped.get(category) ?? []), item])
}

const escapeHtml = (value: unknown): string =>
  String(value)
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;")
    .replaceAll('"', "&quot;")
    .replaceAll("'", "&#039;")

const itemId = (item: ApiItem): string =>
  `${item.kind}-${item.name.toLowerCase()}`
const repositoryValue =
  typeof packageJson.repository === "string"
    ? packageJson.repository
    : packageJson.repository.url
const repository = repositoryValue
  .replace(/^git\+/, "")
  .replace(/^git@github\.com:/, "https://github.com/")
  .replace(/\.git$/, "")

const renderItem = (item: ApiItem): string => {
  const docs = item.docstrings
    .map(doc => `<p>${escapeHtml(doc)}</p>`)
    .join("")
  const sourceUrl = `${repository}/blob/HEAD/${item.source.filepath}#L${item.source.line}`

  return `
    <article class="api-card" id="${itemId(item)}" data-search="${escapeHtml(`${item.name} ${item.signature} ${item.docstrings.join(" ")}`.toLowerCase())}">
      <div class="api-heading">
        <div>
          <span class="kind">${escapeHtml(item.kind)}</span>
          <h3>${escapeHtml(item.name)}</h3>
        </div>
        <a class="source-link" href="${sourceUrl}">Source ↗</a>
      </div>
      ${docs}
      <pre><code>${escapeHtml(item.signature)}</code></pre>
    </article>`
}

const navigation = [...grouped]
  .filter(([, items]) => items.length > 0)
  .map(
    ([category, items]) => `
      <a href="#${category.toLowerCase()}">
        <span>${category}</span>
        <span class="count">${items.length}</span>
      </a>`,
  )
  .join("")

const sections = [...grouped]
  .filter(([, items]) => items.length > 0)
  .map(
    ([category, items]) => `
      <section id="${category.toLowerCase()}">
        <div class="section-heading">
          <p>Extracted kind</p>
          <h2>${category}</h2>
        </div>
        <div class="api-list">${items.map(renderItem).join("")}</div>
      </section>`,
  )
  .join("")

const html = `<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="ReScript bindings for @ctrl/tinycolor">
    <link rel="icon" href="data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 32 32'%3E%3Ccircle cx='16' cy='16' r='14' fill='%23ff6b4a'/%3E%3C/svg%3E">
    <title>${escapeHtml(packageJson.name)} · API</title>
    <style>
      :root {
        color-scheme: dark;
        --background: #101113;
        --panel: #181a1e;
        --panel-soft: #202329;
        --text: #f5f1e8;
        --muted: #aaa69d;
        --line: #32353d;
        --accent: #ff6b4a;
        --accent-soft: #3b2521;
        --code: #ddd6c8;
      }
      * { box-sizing: border-box; }
      html { scroll-behavior: smooth; }
      body {
        margin: 0;
        background:
          radial-gradient(circle at 85% 0%, #39241f 0, transparent 28rem),
          var(--background);
        color: var(--text);
        font-family: Inter, ui-sans-serif, system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
        line-height: 1.6;
      }
      a { color: inherit; }
      .shell { width: 100%; max-width: 1180px; margin: 0 auto; padding-inline: 1rem; }
      header { padding: 5rem 0 4rem; border-bottom: 1px solid var(--line); }
      .eyebrow, .section-heading p {
        margin: 0 0 .65rem;
        color: var(--accent);
        font-size: .74rem;
        font-weight: 800;
        letter-spacing: .16em;
        text-transform: uppercase;
      }
      h1 { max-width: 100%; margin: 0; overflow-wrap: anywhere; font-size: clamp(2.6rem, 8vw, 6.2rem); line-height: .95; letter-spacing: -.065em; }
      .lede { max-width: 680px; margin: 1.6rem 0 0; color: var(--muted); font-size: 1.12rem; }
      .actions { display: flex; flex-wrap: wrap; gap: .75rem; margin-top: 2rem; }
      .button {
        display: inline-flex;
        align-items: center;
        max-width: 100%;
        min-height: 2.65rem;
        padding: .55rem 1rem;
        border: 1px solid var(--line);
        border-radius: 999px;
        background: var(--panel);
        text-decoration: none;
        font-size: .9rem;
        font-weight: 700;
        overflow-wrap: anywhere;
      }
      .button.primary { border-color: var(--accent); background: var(--accent); color: #1e100d; }
      .version { color: var(--muted); }
      .layout { display: grid; grid-template-columns: 220px minmax(0, 1fr); gap: 3rem; padding-block: 3rem 6rem; }
      aside { position: sticky; top: 1.5rem; align-self: start; }
      label { display: block; margin-bottom: .55rem; color: var(--muted); font-size: .78rem; font-weight: 700; }
      input {
        width: 100%;
        padding: .75rem .85rem;
        border: 1px solid var(--line);
        border-radius: .7rem;
        outline: none;
        background: var(--panel);
        color: var(--text);
        font: inherit;
      }
      input:focus { border-color: var(--accent); box-shadow: 0 0 0 3px var(--accent-soft); }
      nav { display: grid; gap: .2rem; margin-top: 1.25rem; }
      nav a { display: flex; justify-content: space-between; padding: .45rem .6rem; border-radius: .45rem; color: var(--muted); text-decoration: none; }
      nav a:hover { background: var(--panel); color: var(--text); }
      .count { font-variant-numeric: tabular-nums; }
      main { min-width: 0; }
      section { scroll-margin-top: 1.5rem; margin-bottom: 4rem; }
      .section-heading { margin-bottom: 1rem; }
      h2 { margin: 0; font-size: 2rem; letter-spacing: -.035em; }
      .api-list { display: grid; grid-template-columns: minmax(0, 1fr); gap: .8rem; min-width: 0; }
      .api-card {
        scroll-margin-top: 1.5rem;
        min-width: 0;
        padding: 1.15rem;
        border: 1px solid var(--line);
        border-radius: .9rem;
        background: color-mix(in srgb, var(--panel) 94%, transparent);
      }
      .api-card[hidden] { display: none; }
      .api-heading { display: flex; align-items: start; justify-content: space-between; gap: 1rem; }
      .api-heading > div { display: flex; align-items: center; gap: .7rem; min-width: 0; }
      .api-card h3 { margin: 0; overflow-wrap: anywhere; font-size: 1.06rem; }
      .kind { padding: .15rem .45rem; border-radius: .35rem; background: var(--accent-soft); color: #ff9a82; font: 700 .68rem ui-monospace, monospace; text-transform: uppercase; }
      .source-link { color: var(--muted); font-size: .78rem; text-decoration: none; white-space: nowrap; }
      .source-link:hover { color: var(--accent); }
      .api-card p { margin: .8rem 0 0; color: var(--muted); }
      pre { max-width: 100%; overflow-x: auto; margin: .9rem 0 0; padding: .85rem 1rem; border-radius: .6rem; background: #0c0d0f; color: var(--code); font-size: .84rem; line-height: 1.55; }
      code { font-family: "SFMono-Regular", Consolas, "Liberation Mono", monospace; }
      .empty { display: none; padding: 4rem 1rem; color: var(--muted); text-align: center; }
      .empty.visible { display: block; }
      footer { padding: 1.5rem 0; border-top: 1px solid var(--line); color: var(--muted); font-size: .82rem; }
      @media (max-width: 760px) {
        header { padding: 3.5rem 0 3rem; }
        .layout { grid-template-columns: minmax(0, 1fr); gap: 2.5rem; }
        aside { position: static; }
        nav { grid-template-columns: repeat(2, 1fr); }
      }
    </style>
  </head>
  <body>
    <header>
      <div class="shell">
        <p class="eyebrow">Generated ReScript API reference</p>
        <h1>${escapeHtml(packageJson.name)}</h1>
        <p class="lede">ReScript bindings for <a href="https://www.npmjs.com/package/@ctrl/tinycolor"><code>@ctrl/tinycolor</code></a>, providing typed color manipulation and conversion.</p>
        <div class="actions">
          <a class="button primary" href="https://www.npmjs.com/package/${escapeHtml(packageJson.name)}">npm install ${escapeHtml(packageJson.name)}</a>
          <a class="button" href="${repository}">GitHub ↗</a>
          <span class="button version">v${escapeHtml(packageJson.version)} · ${apiItems.length} API entries</span>
        </div>
      </div>
    </header>
    <div class="shell layout">
      <aside>
        <label for="api-search">FILTER THE API</label>
        <input id="api-search" type="search" placeholder="Try “hex” or “contrast”" autocomplete="off">
        <nav aria-label="API sections">${navigation}</nav>
      </aside>
      <main>
        ${sections}
        <p class="empty" id="empty-state">No API entries match that search.</p>
      </main>
    </div>
    <footer><div class="shell">Generated from <code>${sourceFile}</code> with the ReScript documentation extractor.</div></footer>
    <script>
      const search = document.querySelector("#api-search")
      const cards = [...document.querySelectorAll(".api-card")]
      const sections = [...document.querySelectorAll("main section")]
      const empty = document.querySelector("#empty-state")

      search.addEventListener("input", event => {
        const query = event.target.value.trim().toLowerCase()
        for (const card of cards) card.hidden = !card.dataset.search.includes(query)
        for (const section of sections) {
          section.hidden = !section.querySelector(".api-card:not([hidden])")
        }
        empty.classList.toggle("visible", cards.every(card => card.hidden))
      })
    </script>
  </body>
</html>
`

mkdirSync(outputDirectory, {recursive: true})
writeFileSync(join(outputDirectory, "index.html"), html)
writeFileSync(join(outputDirectory, "api.json"), `${JSON.stringify(documentation, null, 2)}\n`)
writeFileSync(join(outputDirectory, ".nojekyll"), "")

console.log(`Generated ${apiItems.length} API entries from ${sourceFile}`)
