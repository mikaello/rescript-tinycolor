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

/* CREATE COLOR */

[@bs.module "@ctrl/tinycolor"] external make: 'tinyColor => t = "tinycolor";

[@bs.get] external isValid: t => bool = "";

let returnSomeIfValid = (color: t): option(t) =>
  if (isValid(color)) {
    Some(color);
  } else {
    None;
  };

let makeFromString = (color: string) => returnSomeIfValid(make(color));
let makeFromRgb = (color: rgb) =>
  color |> rgbToJs |> make |> returnSomeIfValid;
let makeFromRgba = (color: rgba) =>
  color |> rgbaToJs |> make |> returnSomeIfValid;
let makeFromRgbRatio = (color: rgbRatio) =>
  color |> rgbRatioToJs |> make |> returnSomeIfValid;
let makeFromRgbaRatio = (color: rgbaRatio) =>
  color |> rgbaRatioToJs |> make |> returnSomeIfValid;
let makeFromHsl = (color: hsl) =>
  color |> hslToJs |> make |> returnSomeIfValid;
let makeFromHsla = (color: hsla) =>
  color |> hslaToJs |> make |> returnSomeIfValid;
let makeFromHslRatio = (color: hslRatio) =>
  color |> hslRatioToJs |> make |> returnSomeIfValid;
let makeFromHslaRatio = (color: hslaRatio) =>
  color |> hslaRatioToJs |> make |> returnSomeIfValid;
let makeFromHsv = (color: hsv) =>
  color |> hsvToJs |> make |> returnSomeIfValid;
let makeFromHsva = (color: hsva) =>
  color |> hsvaToJs |> make |> returnSomeIfValid;
let makeFromHsvRatio = (color: hsvRatio) =>
  color |> hsvRatioToJs |> make |> returnSomeIfValid;
let makeFromHsvaRatio = (color: hsvaRatio) =>
  color |> hsvaRatioToJs |> make |> returnSomeIfValid;

/* GET COLOR PROPERTIES */

[@bs.get] external getFormat: t => string = "format";

[@bs.get] external getOriginalInput: t => 'tinyColor = "originalInput";
[@bs.send] external getBrightness: t => float = "";
[@bs.send] external isLight: t => bool = "";
[@bs.send] external isDark: t => bool = "";
[@bs.send] external getLuminance: t => float = "";
[@bs.send] external getAlpha: t => float = "";
[@bs.send] external setAlpha: (t, float) => t = "";
[@bs.send] external clone: t => t = "";

let setAlpha = (alphaValue: float, color: t): t => {
  let colorClone = clone(color);
  setAlpha(colorClone, alphaValue);
};

/* STRING REPRESENTATIONS */

[@bs.send] external toHsv: t => Js.t('hsv) = "";
let toHsv = (color: t) => toHsv(color) |> hsvaFromJs;
[@bs.send] external toHsvString: t => string = "";
[@bs.send] external toHsl: t => Js.t('hsl) = "";
let toHsl = (color: t) => toHsl(color) |> hslaFromJs;
[@bs.send] external toHslString: t => string = "";
[@bs.send] external toHex: t => string = "";
[@bs.send] external toHexString: t => string = "";
[@bs.send] external toHex8: t => string = "";
[@bs.send] external toHex8String: t => string = "";
[@bs.send] external toRgb: t => Js.t('rgb) = "";
let toRgb = (color: t) => toRgb(color) |> rgbaFromJs;
[@bs.send] external toRgbString: t => string = "";
[@bs.send] external toPercentageRgb: t => Js.t('rgbaPercent) = "";
let toPercentageRgb = (color: t) =>
  toPercentageRgb(color) |> rgbaPercentageFromJs;
[@bs.send] external toPercentageRgbString: t => string = "";
[@bs.send] external toName: t => 'maybeName = "";
let toName = (color: t) => {
  let name = toName(color);
  if (Js.typeof(name) === "string") {
    Some(name);
  } else {
    None;
  };
};
[@bs.module "@ctrl/tinycolor"]
external toMsFilter: (string, string) => string = "";
[@bs.send] external toString: t => string = "";

/* COLOR MODIFICATION */

let callIfValidModificationValue = (value, modFun, color) =>
  if (value >= 0 && value <= 100) {
    Some(modFun(color, value));
  } else {
    None;
  };

[@bs.send] external lighten: (t, int) => t = "";
let lighten = (~value: int=10, color: option(t)) =>
  Belt.Option.flatMap(color, callIfValidModificationValue(value, lighten));

[@bs.send] external brighten: (t, int) => t = "";
let brighten = (~value: int=10, color: option(t)) =>
  Belt.Option.flatMap(color, callIfValidModificationValue(value, brighten));

[@bs.send] external darken: (t, int) => t = "";
let darken = (~value: int=10, color: option(t)) =>
  Belt.Option.flatMap(color, callIfValidModificationValue(value, darken));

[@bs.send] external tint: (t, int) => t = "";
let tint = (~value: int=10, color: option(t)) =>
  Belt.Option.flatMap(color, callIfValidModificationValue(value, tint));

[@bs.send] external shade: (t, int) => t = "";
let shade = (~value: int=10, color: option(t)) =>
  Belt.Option.flatMap(color, callIfValidModificationValue(value, shade));

[@bs.send] external desaturate: (t, int) => t = "";
let desaturate = (~value: int=10, color: option(t)) =>
  Belt.Option.flatMap(
    color,
    callIfValidModificationValue(value, desaturate),
  );

[@bs.send] external saturate: (t, int) => t = "";
let saturate = (~value: int=10, color: option(t)) =>
  Belt.Option.flatMap(color, callIfValidModificationValue(value, saturate));

[@bs.send] external spin: (t, int) => t = "";
let spin = (~value: int=10, color: option(t)) => {
  let callSpin = color' => spin(color', value);
  Belt.Option.map(color, callSpin);
};

[@bs.send] external greyscale: t => t = "";
let greyscale = (color: option(t)) => Belt.Option.map(color, greyscale);

/* COLOR COMBINATIONS */

/*
 analogous
 monochromatic
 splitcomplement
 triad
 tetrad
 polyad
 complement
 */

/* COLOR UTILITIES */