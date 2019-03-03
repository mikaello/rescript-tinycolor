open Jest;
open Expect;
open! Expect.Operators;

open Belt;

describe("making tinycolor", () => {
  test("fromString() returns valid from string", () => {
    let black = TinyColor.makeFromString("black");
    expect(Option.isSome(black)) === true;
  });

  test("fromString() returns valid from hex", () => {
    let white = TinyColor.makeFromString("#fff");
    expect(Option.isSome(white)) === true;
  });

  test("fromString() returns valid from rgb", () => {
    let middle = TinyColor.makeFromString("rgba (160, 160, 160, .5)");
    expect(Option.isSome(middle)) === true;
  });

  test("fromString() returns None when invalid", () => {
    let rubbish = TinyColor.makeFromString("not a color");
    expect(Option.isNone(rubbish)) |> toBe(true);
  });

  test("makeFromRgb() returns valid", () => {
    let a = TinyColor.makeFromRgb({r: 100, g: 100, b: 100});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromRgb() returns correct format", () => {
    let a = TinyColor.makeFromRgb({r: 100, g: 100, b: 100});
    expect(Option.map(a, TinyColor.getFormat)) === Some("rgb");
  });
  test("makeFromRgba() returns valid", () => {
    let a = TinyColor.makeFromRgba({r: 100, g: 100, b: 100, a: 0.1});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromRgba() returns correct format", () => {
    let a = TinyColor.makeFromRgba({r: 100, g: 100, b: 100, a: 0.7});
    expect(Option.map(a, TinyColor.getFormat)) === Some("rgb");
  });
  test("makeFromRgbRatio() returns valid", () => {
    let a = TinyColor.makeFromRgbRatio({r: 0.1, g: 1.0, b: 1.0});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromRgbRatio() returns correct format", () => {
    let a = TinyColor.makeFromRgbRatio({r: 0.1, g: 0.5, b: 0.7});
    expect(Option.map(a, TinyColor.getFormat)) === Some("rgb");
  });
  test("makeFromRgbaRatio() returns valid", () => {
    let a = TinyColor.makeFromRgbaRatio({r: 0.1, g: 0.5, b: 0.7, a: 0.7});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromRgbaRatio() stores all values", () => {
    let input: TinyColor.rgbaRatio = {r: 0.1, g: 0.5, b: 0.7, a: 0.7};
    let a = TinyColor.makeFromRgbaRatio(input);

    expect(Option.map(a, TinyColor.getOriginalInput))
    |> toEqual(Some(TinyColor.rgbaRatioToJs(input)));
  });

  test("makeFromHsl() returns valid", () => {
    let a = TinyColor.makeFromHsl({h: 100, s: 100, l: 100});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHsl() returns correct format", () => {
    let a = TinyColor.makeFromHsl({h: 100, s: 100, l: 100});
    expect(Option.map(a, TinyColor.getFormat)) === Some("hsl");
  });
  test("makeFromHsla() returns valid", () => {
    let a = TinyColor.makeFromHsla({h: 100, s: 100, l: 100, a: 0.7});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHslRatio() returns valid", () => {
    let a = TinyColor.makeFromHslRatio({h: 0.1, s: 0.5, l: 0.7});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHslaRatio() returns valid", () => {
    let a = TinyColor.makeFromHslaRatio({h: 0.1, s: 0.5, l: 0.7, a: 0.7});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHslaRatio() stores all values", () => {
    let input: TinyColor.hslaRatio = {h: 0.1, s: 0.5, l: 0.7, a: 0.7};
    let a = TinyColor.makeFromHslaRatio(input);

    expect(Option.map(a, TinyColor.getOriginalInput))
    |> toEqual(Some(TinyColor.hslaRatioToJs(input)));
  });

  test("makeFromHsv() returns valid", () => {
    let a = TinyColor.makeFromHsv({h: 100, s: 100, v: 100});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHsv() returns correct format", () => {
    let a = TinyColor.makeFromHsv({h: 100, s: 100, v: 100});
    expect(Option.map(a, TinyColor.getFormat)) === Some("hsv");
  });
  test("makeFromHsva() returns valid", () => {
    let a = TinyColor.makeFromHsva({h: 100, s: 100, v: 100, a: 0.7});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHsvRatio() returns valid", () => {
    let a = TinyColor.makeFromHsvRatio({h: 0.1, s: 0.5, v: 0.7});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHsvaRatio() returns valid", () => {
    let a = TinyColor.makeFromHsvaRatio({h: 0.1, s: 0.5, v: 0.7, a: 0.7});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHsvaRatio() stores all values", () => {
    let input: TinyColor.hsvaRatio = {h: 0.1, s: 0.5, v: 0.7, a: 0.7};
    let a = TinyColor.makeFromHsvaRatio(input);

    expect(Option.map(a, TinyColor.getOriginalInput))
    |> toEqual(Some(TinyColor.hsvaRatioToJs(input)));
  });
});

describe("set and get alpha (also tests clone())", () => {
  test("getting alpha value", () => {
    let alphaValue = 0.7;
    let a = TinyColor.makeFromHsla({h: 10, s: 10, l: 10, a: alphaValue});
    expect(Option.map(a, TinyColor.getAlpha)) === Some(alphaValue);
  });

  test("setting alpha value does not alter original tinycolor object", () => {
    let oldAlpha = 0.2;
    let newAlpha = 0.9;

    let a = TinyColor.makeFromHsva({h: 10, s: 10, v: 10, a: oldAlpha});
    Option.map(a, TinyColor.setAlpha(newAlpha)) |> ignore;
    expect(Option.map(a, TinyColor.getAlpha)) === Some(oldAlpha);
  });

  test("setting alpha value updates new object", () => {
    let oldAlpha = 0.2;
    let newAlpha = 0.9;

    let a = TinyColor.makeFromHsva({h: 10, s: 10, v: 10, a: oldAlpha});
    let b = Option.map(a, TinyColor.setAlpha(newAlpha));
    expect(Option.map(b, TinyColor.getAlpha)) === Some(newAlpha);
  });
});

describe("getBrightness()", () => {
  test("getting brightness for light color", () => {
    let color = TinyColor.makeFromString("white");
    expect(Option.map(color, TinyColor.getLuminance)) === Some(1.0);
  });
  test("getting brightness for dark color", () => {
    let color = TinyColor.makeFromString("black");
    expect(Option.map(color, TinyColor.getLuminance)) === Some(0.0);
  });
});
describe("isLight()", () =>
  test("that light color is returned as light", () => {
    let light = TinyColor.makeFromString("white");
    expect(Option.map(light, TinyColor.isLight)) === Some(true);
  })
);
describe("isDark()", () =>
  test("that dark color is returned as dark", () => {
    let black = TinyColor.makeFromString("black");
    expect(Option.map(black, TinyColor.isDark)) === Some(true);
  })
);
describe("getLuminance()", () => {
  test("getting luminance for dark color", () => {
    let color = TinyColor.makeFromString("black");
    expect(Option.map(color, TinyColor.getLuminance)) === Some(0.0);
  });
  test("getting luminance for light color", () => {
    let color = TinyColor.makeFromString("white");
    expect(Option.map(color, TinyColor.getLuminance)) === Some(1.0);
  });
});