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
  s: int,
  l: int,
};

[@bs.deriving jsConverter]
type hsla = {
  h: int,
  s: int,
  l: int,
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
  s: int,
  v: int,
};

[@bs.deriving jsConverter]
type hsva = {
  h: int,
  s: int,
  v: int,
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

[@bs.module "@ctrl/tinycolor"] external make: 'tinyColor => t = "tinycolor";

[@bs.get] external isValid: t => bool = "";
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