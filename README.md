# (WIP) bs-tinycolor

[![Build Status](https://travis-ci.org/mikaello/bs-tinycolor.svg?branch=master)](https://travis-ci.org/mikaello/bs-tinycolor)

🚧 **UNDER CONSTRUCTION** 🚧

Bucklescript bindings for [TinyColor](https://github.com/bgrins/TinyColor): fast, small color manipulation and conversion. See also https://bgrins.github.io/TinyColor/

## Getting started

```
yarn add https://github.com/mikaello/bs-tinycolor
```

Then add `bs-tinycolor` as a dependency to `bsconfig.json`:

```diff
"bs-dependencies": [
+  "bs-tinycolor"
]
```

## Example

```reason
open BsTinycolor;

/* Examples of bs-tinycolor here */
```

## Differences from original

- It is not possible to create a invalid tinycolor instance, it will either return `Some(t)` if it is valid, or `None` if it is invalid
- `setAlpha(val)` is immutable, it will return a new instance with changed alpha value
- `toName()` returns an option, either `Some(string)` if a name could be deduced (e.g. _red_) or `None` if not

## Contribute

If you find bugs or there are updates in [TinyColor](https://github.com/bgrins/TinyColor), feel free to open an issue or PR. If you are upgrading any dependencies, please use yarn so `yarn.lock` is updated.

If you add, remove or change bindings, remember to update the tests as well. It should be at least one test for every binding. Run the tests with `yarn test` from project root.

## Alternatives

- [bs-parse-color](https://redex.github.io/package/unpublished/theatlasroom/bs-parse-color/) (bindings for [parse-color](https://github.com/substack/parse-color))
