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

## Contribute

If you find bugs or there are updates in [TinyColor](https://github.com/bgrins/TinyColor), feel free to open an issue or PR. If you are upgrading any dependencies, please use yarn so `yarn.lock` is updated.

## Alternatives

- [bs-parse-color](https://redex.github.io/package/unpublished/theatlasroom/bs-parse-color/) (bindings for [parse-color](https://github.com/substack/parse-color))
