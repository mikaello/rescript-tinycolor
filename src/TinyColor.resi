/** A validated TinyColor instance. */
type t

/** An RGB color with channels from 0 through 255. */
type rgb = {
  r: int,
  g: int,
  b: int,
}

/** An RGB color with channels from 0 through 255 and alpha from 0.0 through 1.0. */
type rgba = {
  r: int,
  g: int,
  b: int,
  a: float,
}

/** An RGB color expressed as percentages and alpha from 0.0 through 1.0. */
type rgbaPercentage = {
  r: string,
  g: string,
  b: string,
  a: float,
}

/** An RGB color with channels expressed as ratios from 0.0 through 1.0. */
type rgbRatio = {
  r: float,
  g: float,
  b: float,
}

/** An RGB color with channels and alpha expressed as ratios from 0.0 through 1.0. */
type rgbaRatio = {
  r: float,
  g: float,
  b: float,
  a: float,
}

/** An HSL color with hue in degrees and saturation and lightness as ratios. */
type hsl = {
  h: int,
  s: float,
  l: float,
}

/** An HSL color with hue in degrees and the other values expressed as ratios. */
type hsla = {
  h: int,
  s: float,
  l: float,
  a: float,
}

/** An HSL color with every value expressed as a ratio from 0.0 through 1.0. */
type hslRatio = {
  h: float,
  s: float,
  l: float,
}

/** An HSLA color with every value expressed as a ratio from 0.0 through 1.0. */
type hslaRatio = {
  h: float,
  s: float,
  l: float,
  a: float,
}

/** An HSV color with hue in degrees and saturation and value as ratios. */
type hsv = {
  h: int,
  s: float,
  v: float,
}

/** An HSV color with hue in degrees and the other values expressed as ratios. */
type hsva = {
  h: int,
  s: float,
  v: float,
  a: float,
}

/** An HSV color with every value expressed as a ratio from 0.0 through 1.0. */
type hsvRatio = {
  h: float,
  s: float,
  v: float,
}

/** An HSVA color with every value expressed as a ratio from 0.0 through 1.0. */
type hsvaRatio = {
  h: float,
  s: float,
  v: float,
  a: float,
}

/** A CMYK color with values from 0 through 100. */
type cmyk = {
  c: int,
  m: int,
  y: int,
  k: int,
}

/** Returns whether a TinyColor instance is valid. */
let isValid: t => bool

/** Returns whether a color has no saturation. */
let isMonochrome: t => bool

/** Creates a color from a CSS color name, hex value, or color function. */
let makeFromString: string => option<t>

/** Creates a color from a non-negative numeric color value. */
let makeFromNumber: int => option<t>

/** Creates a color from RGB channels from 0 through 255. */
let makeFromRgb: rgb => option<t>

/** Creates a color from RGB channels from 0 through 255 and alpha from 0.0 through 1.0. */
let makeFromRgba: rgba => option<t>

/** Creates a color from RGB channel ratios from 0.0 through 1.0. */
let makeFromRgbRatio: rgbRatio => option<t>

/** Creates a color from RGB channel and alpha ratios from 0.0 through 1.0. */
let makeFromRgbaRatio: rgbaRatio => option<t>

/** Creates a color from a hue in degrees and saturation and lightness ratios. */
let makeFromHsl: hsl => option<t>

/** Creates a color from a hue in degrees and saturation, lightness, and alpha ratios. */
let makeFromHsla: hsla => option<t>

/** Creates a color from HSL ratios from 0.0 through 1.0. */
let makeFromHslRatio: hslRatio => option<t>

/** Creates a color from HSLA ratios from 0.0 through 1.0. */
let makeFromHslaRatio: hslaRatio => option<t>

/** Creates a color from a hue in degrees and saturation and value ratios. */
let makeFromHsv: hsv => option<t>

/** Creates a color from a hue in degrees and saturation, value, and alpha ratios. */
let makeFromHsva: hsva => option<t>

/** Creates a color from HSV ratios from 0.0 through 1.0. */
let makeFromHsvRatio: hsvRatio => option<t>

/** Creates a color from HSVA ratios from 0.0 through 1.0. */
let makeFromHsvaRatio: hsvaRatio => option<t>

/** Creates a color from CMYK values from 0 through 100. */
let makeFromCmyk: cmyk => option<t>

/** Returns the format used to create the color. */
let getFormat: t => string

/** Returns the original color input as JSON. */
let getOriginalInput: t => JSON.t

/** Returns perceived brightness from 0.0 through 255.0. */
let getBrightness: t => float

/** Returns whether the color is considered light. */
let isLight: t => bool

/** Returns whether the color is considered dark. */
let isDark: t => bool

/** Returns relative luminance from 0.0 through 1.0. */
let getLuminance: t => float

/** Returns alpha from 0.0 through 1.0. */
let getAlpha: t => float

/** Returns a copy with the supplied alpha value. */
let setAlpha: (float, t) => t

/** Returns the numeric RGB representation of the color. */
let toNumber: t => int

/** Returns a copy of the color. */
let clone: t => t

/** Composites the color over a background color. */
let onBackground: (t, t) => t

/** Converts the color to HSVA. */
let toHsv: t => hsva

/** Converts the color to an HSV or HSVA string. */
let toHsvString: t => string

/** Converts the color to HSLA. */
let toHsl: t => hsla

/** Converts the color to an HSL or HSLA string. */
let toHslString: t => string

/** Converts the color to a hex value without a leading hash. */
let toHex: t => string

/** Converts the color to a six-digit hex string. */
let toHexString: t => string

/** Converts the color to an eight-digit hex value without a leading hash. */
let toHex8: t => string

/** Converts the color to an eight-digit hex string. */
let toHex8String: t => string

/** Converts the color to the shortest equivalent hex string. */
let toHexShortString: t => string

/** Converts the color to RGBA. */
let toRgb: t => rgba

/** Converts the color to an RGB or RGBA string. */
let toRgbString: t => string

/** Converts the color to percentage RGBA. */
let toPercentageRgb: t => rgbaPercentage

/** Converts the color to a percentage RGB or RGBA string. */
let toPercentageRgbString: t => string

/** Converts the color to CMYK. */
let toCmyk: t => cmyk

/** Converts the color to a CMYK string. */
let toCmykString: t => string

/** Returns the CSS color name when one exactly matches. */
let toName: t => option<string>

/** Creates a Microsoft gradient filter from two color strings. */
let toMsFilter: (string, string) => string

/** Converts the color to a string using its original format when possible. */
let toString: t => string

/** Lightens the color by a percentage from 0 through 100. */
let lighten: (~value: int=?, t) => option<t>

/** Brightens the color by a percentage from 0 through 100. */
let brighten: (~value: int=?, t) => option<t>

/** Darkens the color by a percentage from 0 through 100. */
let darken: (~value: int=?, t) => option<t>

/** Mixes the color with white by a percentage from 0 through 100. */
let tint: (~value: int=?, t) => option<t>

/** Mixes the color with black by a percentage from 0 through 100. */
let shade: (~value: int=?, t) => option<t>

/** Decreases saturation by a percentage from 0 through 100. */
let desaturate: (~value: int=?, t) => option<t>

/** Increases saturation by a percentage from 0 through 100. */
let saturate: (~value: int=?, t) => option<t>

/** Rotates the hue by the supplied number of degrees. */
let spin: (~value: int=?, t) => t

/** Mixes two colors using a percentage from 0 through 100. */
let mix: (~value: int=?, t, t) => option<t>

/** Returns the greyscale equivalent of the color. */
let greyscale: t => t

/** Returns an analogous color scheme. */
let analogous: (t, ~results: int=?, ~slices: int=?, unit) => array<t>

/** Returns a monochromatic color scheme. */
let monochromatic: (t, ~results: int=?, unit) => array<t>

/** Returns a split-complementary color scheme. */
let splitcomplement: t => array<t>

/** Returns a triadic color scheme. */
let triad: t => array<t>

/** Returns a tetradic color scheme. */
let tetrad: t => array<t>

/** Returns a color scheme with the requested number of colors. */
let polyad: (t, ~n: int=?, unit) => array<t>

/** Returns the complementary color. */
let complement: t => t

/** Returns whether two colors have the same RGB and alpha values. */
let equals: (t, t) => bool

/** Returns a random color. */
let random: (
  ~hue: [#red | #orange | #yellow | #green | #blue | #purple | #pink | #monochrome]=?,
  ~luminosity: [#bright | #light | #dark]=?,
  ~seed: int=?,
  ~alpha: float=?,
  unit,
) => t

/** Returns the requested number of random colors. */
let randomMultiple: (
  ~hue: [#red | #orange | #yellow | #green | #blue | #purple | #pink | #monochrome]=?,
  ~luminosity: [#bright | #light | #dark]=?,
  ~seed: int=?,
  ~alpha: float=?,
  ~count: int,
  unit,
) => array<t>

/** Returns the WCAG contrast ratio between two colors. */
let readability: (t, t) => float

/** Returns whether two colors meet the requested WCAG readability level. */
let isReadable: (~level: [#AA | #AAA]=?, ~size: [#small | #large]=?, t, t) => bool

/** Returns the most readable color from a list of candidates. */
let mostReadable: (
  ~includeFallbackColors: bool=?,
  ~level: [#AA | #AAA]=?,
  ~size: [#small | #large]=?,
  array<t>,
  t,
) => option<t>
