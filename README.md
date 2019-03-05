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

- It is not possible to create an invalid tinycolor instance, it will either return `Some(t)` if it is valid, or `None` if it is invalid. E.g. an invalid instance can occur if you create a color with a string not corresponding to a valid color (`beautifulRed` is not a valid color) or you provide RGB values outside the valid range (0-255).
- All functions accept only TinyColor-instances created by one of the `make-`-functions (or `random()`), it is not possible to pass in a string or RGB-record for the functions (which is possible in the original library).
- `setAlpha(val)` is immutable, it will return a new instance with changed alpha value (the other methods that modify a color (`spin`, `lighten`, etc.) is immutable from the original library)
- `toName()` returns an option, either `Some(string)` if a name could be deduced (e.g. _red_) or `None` if not

## Contribute

If you find bugs or there are updates in [TinyColor](https://github.com/bgrins/TinyColor), feel free to open an issue or PR. If you are upgrading any dependencies, please use yarn so `yarn.lock` is updated.

If you add, remove or change bindings, remember to update the tests as well. It should be at least one test for every binding. Run the tests with `yarn test` from project root.

## Alternatives

- [bs-parse-color](https://redex.github.io/package/unpublished/theatlasroom/bs-parse-color/) (bindings for [parse-color](https://github.com/substack/parse-color))
