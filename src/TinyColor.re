open Belt;
type t;

[@bs.deriving jsConverter]
type rgb = {
  r: int,
  g: int,
  b: int,
};

[@bs.deriving jsConverter]
type rgba = {
  r: int,
  g: int,
  b: int,
  a: float,
};

[@bs.deriving jsConverter]
type rgbaPercentage = {
  r: string,
  g: string,
  b: string,
  a: float,
};

[@bs.deriving jsConverter]
type rgbRatio = {
  r: float,
  g: float,
  b: float,
};

[@bs.deriving jsConverter]
type rgbaRatio = {
  r: float,
  g: float,
  b: float,
  a: float,
};

[@bs.deriving jsConverter]
type hsl = {
  h: int,
  s: float,
  l: float,
};

[@bs.deriving jsConverter]
type hsla = {
  h: int,
  s: float,
  l: float,
  a: float,
};

[@bs.deriving jsConverter]
type hslRatio = {
  h: float,
  s: float,
  l: float,
};

[@bs.deriving jsConverter]
type hslaRatio = {
  h: float,
  s: float,
  l: float,
  a: float,
};

[@bs.deriving jsConverter]
type hsv = {
  h: int,
  s: float,
  v: float,
};

[@bs.deriving jsConverter]
type hsva = {
  h: int,
  s: float,
  v: float,
  a: float,
};

[@bs.deriving jsConverter]
type hsvRatio = {
  h: float,
  s: float,
  v: float,
};

[@bs.deriving jsConverter]
type hsvaRatio = {
  h: float,
  s: float,
  v: float,
  a: float,
};

/* VALIDATOR UTILS */

[@bs.get] external isValid: t => bool = "isValid";

let returnSomeIfValid = (color: t): option(t) =>
  if (isValid(color)) {
    Some(color);
  } else {
    None;
  };

let isFraction = value => value >= 0.0 && value <= 1.0;
let isValidHue = hue => hue >= 0 && hue <= 360;

let validateColorNumber = (color: int) =>
  if (color >= 0) {
    /* consider also checking if number is more than 0xffffff (16777215) */
    Some(
      color,
    );
  } else {
    None;
  };

let validateRgb = (color: rgb) => {
  let validRgbRange = value => value >= 0 && value <= 255;
  switch (color) {
  | {r, g, b} when validRgbRange(r) && validRgbRange(g) && validRgbRange(b) =>
    Some(color)
  | _ => None
  };
};

let validateRgba = (color: rgba) => {
  switch (color) {
  | {r, g, b, a} when validateRgb({r, g, b}) !== None && isFraction(a) =>
    Some(color)
  | _ => None
  };
};

let validateHsl = (color: hsl) => {
  switch (color) {
  | {h, s, l} when isValidHue(h) && isFraction(s) && isFraction(l) =>
    Some(color)
  | _ => None
  };
};

let validateHsla = (color: hsla) => {
  switch (color) {
  | {h, s, l, a} when validateHsl({h, s, l}) !== None && isFraction(a) =>
    Some(color)
  | _ => None
  };
};

let validateHsv = (color: hsv) => {
  switch (color) {
  | {h, s, v} when isValidHue(h) && isFraction(s) && isFraction(v) =>
    Some(color)
  | _ => None
  };
};

let validateHsva = (color: hsva) => {
  switch (color) {
  | {h, s, v, a} when validateHsv({h, s, v}) !== None && isFraction(a) =>
    Some(color)
  | _ => None
  };
};

/* CREATE COLOR */

[@bs.module "@ctrl/tinycolor"] external make: 'tinyColor => t = "tinycolor";

let makeFromString = (color: string) => returnSomeIfValid(make(color));
let makeFromNumber = (number: int) =>
  (number |> validateColorNumber)
  ->Option.map(make)
  ->Option.flatMap(returnSomeIfValid);
let makeFromRgb = (color: rgb) =>
  (color |> validateRgb)
  ->(Option.map(rgbToJs))
  ->(Option.map(make))
  ->(Option.flatMap(returnSomeIfValid));
let makeFromRgba = (color: rgba) =>
  (color |> validateRgba)
  ->(Option.map(rgbaToJs))
  ->(Option.map(make))
  ->(Option.flatMap(returnSomeIfValid));
let makeFromRgbRatio = (color: rgbRatio) =>
  color |> rgbRatioToJs |> make |> returnSomeIfValid;
let makeFromRgbaRatio = (color: rgbaRatio) =>
  color |> rgbaRatioToJs |> make |> returnSomeIfValid;
let makeFromHsl = (color: hsl) =>
  (color |> validateHsl)
  ->(Option.map(hslToJs))
  ->(Option.map(make))
  ->(Option.flatMap(returnSomeIfValid));
let makeFromHsla = (color: hsla) =>
  (color |> validateHsla)
  ->(Option.map(hslaToJs))
  ->(Option.map(make))
  ->(Option.flatMap(returnSomeIfValid));
let makeFromHslRatio = (color: hslRatio) =>
  color |> hslRatioToJs |> make |> returnSomeIfValid;
let makeFromHslaRatio = (color: hslaRatio) =>
  color |> hslaRatioToJs |> make |> returnSomeIfValid;
let makeFromHsv = (color: hsv) =>
  (color |> validateHsv)
  ->(Option.map(hsvToJs))
  ->(Option.map(make))
  ->(Option.flatMap(returnSomeIfValid));
let makeFromHsva = (color: hsva) =>
  (color |> validateHsva)
  ->(Option.map(hsvaToJs))
  ->(Option.map(make))
  ->(Option.flatMap(returnSomeIfValid));
let makeFromHsvRatio = (color: hsvRatio) =>
  color |> hsvRatioToJs |> make |> returnSomeIfValid;
let makeFromHsvaRatio = (color: hsvaRatio) =>
  color |> hsvaRatioToJs |> make |> returnSomeIfValid;

/* GET COLOR PROPERTIES */

[@bs.get] external getFormat: t => string = "format";

[@bs.get] external getOriginalInput: t => 'tinyColor = "originalInput";
[@bs.send] external getBrightness: t => float = "getBrightness";
[@bs.send] external isLight: t => bool = "isLight";
[@bs.send] external isDark: t => bool = "isDark";
[@bs.send] external getLuminance: t => float = "getLuminance";
[@bs.send] external getAlpha: t => float = "getAlpha";
[@bs.send] external setAlpha: (t, float) => t = "setAlpha";
[@bs.send] external toNumber: t => int = "toNumber";
[@bs.send] external clone: t => t = "clone";

let setAlpha = (alphaValue: float, color: t): t => {
  let colorClone = clone(color);
  setAlpha(colorClone, alphaValue);
};

/* STRING REPRESENTATIONS */

[@bs.send] external toHsv: t => Js.t('hsv) = "toHsv";
let toHsv = (color: t) => toHsv(color) |> hsvaFromJs;
[@bs.send] external toHsvString: t => string = "toHsvString";
[@bs.send] external toHsl: t => Js.t('hsl) = "toHsl";
let toHsl = (color: t) => toHsl(color) |> hslaFromJs;
[@bs.send] external toHslString: t => string = "toHslString";
[@bs.send] external toHex: t => string = "toHex";
[@bs.send] external toHexString: t => string = "toHexString";
[@bs.send] external toHex8: t => string = "toHex8";
[@bs.send] external toHex8String: t => string = "toHex8String";
[@bs.send] external toRgb: t => Js.t('rgb) = "toRgb";
let toRgb = (color: t) => toRgb(color) |> rgbaFromJs;
[@bs.send] external toRgbString: t => string = "toRgbString";
[@bs.send]
external toPercentageRgb: t => Js.t('rgbaPercent) = "toPercentageRgb";
let toPercentageRgb = (color: t) =>
  toPercentageRgb(color) |> rgbaPercentageFromJs;
[@bs.send]
external toPercentageRgbString: t => string = "toPercentageRgbString";
[@bs.send] external toName: t => 'maybeName = "toName";
let toName = (color: t) => {
  let name = toName(color);
  if (Js.typeof(name) === "string") {
    Some(name);
  } else {
    None;
  };
};
[@bs.module "@ctrl/tinycolor"]
external toMsFilter: (string, string) => string = "toMsFilter";

[@bs.send] external toString: t => string = "toString";

/* COLOR MODIFICATION */

let callIfValidModificationValue = (value, modFun, color) =>
  if (value >= 0 && value <= 100) {
    Some(modFun(color, value));
  } else {
    None;
  };

[@bs.send] external lighten: (t, int) => t = "lighten";
let lighten = (~value: int=10, color: t) =>
  callIfValidModificationValue(value, lighten, color);

[@bs.send] external brighten: (t, int) => t = "brighten";
let brighten = (~value: int=10, color: t) =>
  callIfValidModificationValue(value, brighten, color);

[@bs.send] external darken: (t, int) => t = "darken";
let darken = (~value: int=10, color: t) =>
  callIfValidModificationValue(value, darken, color);

[@bs.send] external tint: (t, int) => t = "tint";
let tint = (~value: int=10, color: t) =>
  callIfValidModificationValue(value, tint, color);

[@bs.send] external shade: (t, int) => t = "shade";
let shade = (~value: int=10, color: t) =>
  callIfValidModificationValue(value, shade, color);

[@bs.send] external desaturate: (t, int) => t = "desaturate";
let desaturate = (~value: int=10, color: t) =>
  callIfValidModificationValue(value, desaturate, color);

[@bs.send] external saturate: (t, int) => t = "saturate";
let saturate = (~value: int=10, color: t) =>
  callIfValidModificationValue(value, saturate, color);

[@bs.send] external spin: (t, int) => t = "spin";
let spin = (~value: int=10, color: t) => {
  spin(color, value);
};

[@bs.send] external mix: (t, t, int) => t = "mix";
let mix = (~value: int=50, color1: t, color2: t) => {
  callIfValidModificationValue(value, mix(color1), color2);
};

[@bs.send] external greyscale: t => t = "greyscale";

/* COLOR COMBINATIONS */

[@bs.send.pipe: t]
external analogous: (~results: int=?, ~slices: int=?) => array(t) =
  "analogous";
[@bs.send.pipe: t]
external monochromatic: (~results: int=?) => array(t) = "monochromatic";
[@bs.send] external splitcomplement: t => array(t) = "splitcomplement";
[@bs.send] external triad: t => array(t) = "triad";
[@bs.send] external tetrad: t => array(t) = "tetrad";
[@bs.send.pipe: t] external polyad: (~n: int=?) => array(t) = "polyad";
[@bs.send] external complement: t => t = "complement";

/* COLOR UTILITIES */

[@bs.send] external equals: (t, t) => bool = "equals";

[@bs.module "@ctrl/tinycolor"] external random: 'config => t = "random";
[@bs.module "@ctrl/tinycolor"]
external randomMultiple: 'config => array(t) = "random";

[@bs.obj]
external randomConfig:
  (
    ~hue: [@bs.string] [
            | `red
            | `orange
            | `yellow
            | `green
            | `blue
            | `purple
            | `pink
            | `monochrome
          ]
            =?,
    ~luminosity: [@bs.string] [ | `bright | `light | `dark]=?,
    ~seed: int=?,
    ~alpha: float=?,
    ~count: int=?,
    unit
  ) =>
  _;

let random =
    (
      ~hue:
         option(
           [
             | `red
             | `orange
             | `yellow
             | `green
             | `blue
             | `purple
             | `pink
             | `monochrome
           ],
         )=?,
      ~luminosity: option([ | `bright | `light | `dark])=?,
      ~seed: option(int)=?,
      ~alpha: option(float)=?,
      (),
    ) =>
  random(randomConfig(~hue?, ~luminosity?, ~seed?, ~alpha?, ()));

let randomMultiple =
    (
      ~hue:
         option(
           [
             | `red
             | `orange
             | `yellow
             | `green
             | `blue
             | `purple
             | `pink
             | `monochrome
           ],
         )=?,
      ~luminosity: option([ | `bright | `light | `dark])=?,
      ~seed: option(int)=?,
      ~alpha: option(float)=?,
      ~count: int,
      (),
    ) =>
  randomMultiple(
    randomConfig(~hue?, ~luminosity?, ~seed?, ~alpha?, ~count, ()),
  );

[@bs.module "@ctrl/tinycolor"]
external readability: (t, t) => float = "readability";

[@bs.obj]
external wcagOption:
  (
    ~level: [@bs.string] [ | `AA | `AAA]=?,
    ~size: [@bs.string] [ | `small | `large]=?
  ) =>
  _;

[@bs.module "@ctrl/tinycolor"]
external isReadable: (t, t, 'wcagObject) => bool = "isReadable";
let isReadable =
    (
      ~level: option([ | `AA | `AAA])=?,
      ~size: option([ | `small | `large])=?,
      color1: t,
      color2: t,
    ) =>
  isReadable(color1, color2, wcagOption(~level?, ~size?));

[@bs.obj]
external mostReadableConfig:
  (
    ~includeFallbackColors: bool=?,
    ~level: [@bs.string] [ | `AA | `AAA]=?,
    ~size: [@bs.string] [ | `small | `large]=?
  ) =>
  _;

[@bs.module "@ctrl/tinycolor"]
external mostReadable: (t, array(t), 'config) => t = "mostReadable";
let mostReadable =
    (
      ~includeFallbackColors=?,
      ~level: option([ | `AA | `AAA])=?,
      ~size: option([ | `small | `large])=?,
      compareColors: array(t),
      color: t,
    ) =>
  mostReadable(
    color,
    compareColors,
    mostReadableConfig(~includeFallbackColors?, ~level?, ~size?),
  );
