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
  test("makeFromRgb() returns None for invalid values", () => {
    let a = TinyColor.makeFromRgb({r: 700, g: 800, b: 100});
    expect(Option.isNone(a)) === true;
  });
  test("makeFromRgb() returns correct format", () => {
    let a = TinyColor.makeFromRgb({r: 100, g: 100, b: 100});
    expect(Option.map(a, TinyColor.getFormat)) === Some("rgb");
  });
  test("makeFromRgba() returns valid", () => {
    let a = TinyColor.makeFromRgba({r: 100, g: 100, b: 100, a: 0.1});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromRgba() returns None for invalid values", () => {
    let a = TinyColor.makeFromRgba({r: 100, g: 100, b: 100, a: 1.1});
    expect(Option.isNone(a)) === true;
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
    let a = TinyColor.makeFromHsl({h: 10, s: 0.10, l: 0.10});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHsl() returns None for invalid values", () => {
    let a = TinyColor.makeFromHsl({h: 370, s: 0.10, l: 0.10});
    expect(Option.isNone(a)) === true;
  });
  test("makeFromHsl() returns correct format", () => {
    let a = TinyColor.makeFromHsl({h: 10, s: 0.10, l: 0.10});
    expect(Option.map(a, TinyColor.getFormat)) === Some("hsl");
  });
  test("makeFromHsla() returns valid", () => {
    let a = TinyColor.makeFromHsla({h: 100, s: 0.10, l: 0.10, a: 0.7});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHsla() returns None for invalid values", () => {
    let a = TinyColor.makeFromHsla({h: 100, s: 2.10, l: 0.10, a: 0.7});
    expect(Option.isNone(a)) === true;
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
    let a = TinyColor.makeFromHsv({h: 1, s: 0.10, v: 0.10});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHsv() returns None for invalid", () => {
    let a = TinyColor.makeFromHsv({h: 1000, s: 0.10, v: 0.10});
    expect(Option.isNone(a)) === true;
  });
  test("makeFromHsv() returns correct format", () => {
    let a = TinyColor.makeFromHsv({h: 10, s: 0.10, v: 0.10});
    expect(Option.map(a, TinyColor.getFormat)) === Some("hsv");
  });
  test("makeFromHsva() returns valid", () => {
    let a = TinyColor.makeFromHsva({h: 100, s: 0.10, v: 0.10, a: 0.7});
    expect(Option.isSome(a)) === true;
  });
  test("makeFromHsva() returns None for invalid", () => {
    let a = TinyColor.makeFromHsva({h: 100, s: 0.10, v: 0.10, a: 3.7});
    expect(Option.isNone(a)) === true;
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
    let a = TinyColor.makeFromHsla({h: 20, s: 0.20, l: 0.20, a: alphaValue});
    expect(Option.map(a, TinyColor.getAlpha)) === Some(alphaValue);
  });

  test("setting alpha value does not alter original tinycolor object", () => {
    let oldAlpha = 0.2;
    let newAlpha = 0.9;

    let a = TinyColor.makeFromHsva({h: 10, s: 0.10, v: 0.10, a: oldAlpha});
    Option.map(a, TinyColor.setAlpha(newAlpha)) |> ignore;
    expect(Option.map(a, TinyColor.getAlpha)) === Some(oldAlpha);
  });

  test("setting alpha value updates new object", () => {
    let oldAlpha = 0.2;
    let newAlpha = 0.9;

    let a = TinyColor.makeFromHsva({h: 100, s: 0.10, v: 0.10, a: oldAlpha});
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

describe("string representation methods", () => {
  let hsv = TinyColor.makeFromHsva({h: 15, s: 0.50, v: 1.0, a: 0.1});
  let hsl = TinyColor.makeFromHsla({h: 280, s: 0.50, l: 0.75, a: 0.5});
  let rgb = TinyColor.makeFromRgba({r: 0, g: 10, b: 20, a: 0.9});
  let shortHex = TinyColor.makeFromString("#678");
  let red = TinyColor.makeFromString("red");

  test("toHsv()", () =>
    expect(Option.map(hsv, TinyColor.toHsv))
    == Some({h: 15, s: 0.50, v: 1.0, a: 0.1})
  );
  test("toHsvString()", () =>
    expect(Option.map(hsv, TinyColor.toHsvString))
    === Some("hsva(15, 50%, 100%, 0.1)")
  );
  test("toHsl()", () =>
    expect(Option.map(hsl, TinyColor.toHsl))
    == Some({h: 280, s: 0.5, l: 0.75, a: 0.5})
  );
  test("toHslString()", () =>
    expect(Option.map(hsl, TinyColor.toHslString))
    === Some("hsla(280, 50%, 75%, 0.5)")
  );
  test("toHex()", () =>
    expect(Option.map(rgb, TinyColor.toHex)) === Some("000a14")
  );
  test("toHexString()", () =>
    expect(Option.map(rgb, TinyColor.toHexString)) === Some("#000a14")
  );
  test("toHex8()", () =>
    expect(Option.map(shortHex, TinyColor.toHex8)) === Some("667788ff")
  );
  test("toHex8String()", () =>
    expect(Option.map(shortHex, TinyColor.toHex8String))
    === Some("#667788ff")
  );
  test("toRgb()", () =>
    expect(Option.map(rgb, TinyColor.toRgb))
    == Some({r: 0, g: 10, b: 20, a: 0.9})
  );
  test("toRgbString()", () =>
    expect(Option.map(rgb, TinyColor.toRgbString))
    === Some("rgba(0, 10, 20, 0.9)")
  );
  test("toPercentageRgb()", () =>
    expect(Option.map(rgb, TinyColor.toPercentageRgb))
    == Some({r: "0%", g: "4%", b: "8%", a: 0.9})
  );
  test("toPercentageRgbString()", () =>
    expect(Option.map(rgb, TinyColor.toPercentageRgbString))
    === Some("rgba(0%, 4%, 8%, 0.9)")
  );
  test("toName() defined", () =>
    expect(Option.map(red, TinyColor.toName)) === Some(Some("red"))
  );
  test("toName() undefined", () =>
    expect(Option.map(rgb, TinyColor.toName)) |> toEqual(Some(None))
  );
  test("toMsFilter()", () =>
    expect(TinyColor.toMsFilter("red", "blue"))
    === "progid:DXImageTransform.Microsoft.gradient(startColorstr=#ffff0000,endColorstr=#ff0000ff)"
  );
  test("toString(), test hex", () =>
    expect(Option.map(shortHex, TinyColor.toString)) === Some("#667788")
  );
});

describe("color modification tests", () => {
  let red = TinyColor.makeFromString("red");

  test("lighten(int, t)", () => {
    let a = TinyColor.lighten(~value=10, red);
    expect(Option.map(a, TinyColor.toHexString))
    |> toEqual(Some("#ff3333"));
  });

  test("lighten(int, t) does not change original instance", () => {
    let a = TinyColor.lighten(~value=10, red);

    expect(Option.map(a, TinyColor.toHex8String))
    |> not
    |> toEqual(Option.map(red, TinyColor.toHex8String));
  });

  test("brighten(int, t)", () => {
    let a = TinyColor.brighten(~value=10, red);
    expect(Option.map(a, TinyColor.toHexString))
    |> toEqual(Some("#ff1919"));
  });

  test("brighten(int, t) dose not change original instance", () => {
    let a = TinyColor.brighten(~value=10, red);

    expect(Option.map(a, TinyColor.toString))
    |> not
    |> toEqual(Option.map(red, TinyColor.toString));
  });

  test("darken(int, t)", () => {
    let a = TinyColor.darken(~value=10, red);
    expect(Option.map(a, TinyColor.toHexString))
    |> toEqual(Some("#cc0000"));
  });

  test("tint(int, t)", () => {
    let a = TinyColor.tint(~value=10, red);
    expect(Option.map(a, TinyColor.toHexString))
    |> toEqual(Some("#ff1a1a"));
  });

  test("shade(int, t)", () => {
    let a = TinyColor.shade(~value=10, red);
    expect(Option.map(a, TinyColor.toHexString))
    |> toEqual(Some("#e60000"));
  });

  test("desaturate(int, t)", () => {
    let a = TinyColor.desaturate(~value=10, red);
    expect(Option.map(a, TinyColor.toHexString))
    |> toEqual(Some("#f20d0d"));
  });

  test("saturate(int, t)", () => {
    let a = TinyColor.saturate(~value=10, red);
    expect(Option.map(a, TinyColor.toHexString))
    |> toEqual(Some("#ff0000"));
  });

  test("spin(int, t)", () => {
    let a = TinyColor.spin(~value=180, red);
    expect(Option.map(a, TinyColor.toHex8String)) === Some("#00ffffff");
  });

  test("spin(int, t) with value 360 does not change", () => {
    let a = TinyColor.spin(~value=360, red);
    expect(Option.map(a, TinyColor.toHex8String))
    === Option.map(red, TinyColor.toHex8String);
  });

  test("greyscale(t)", () => {
    let a = TinyColor.greyscale(red);
    expect(Option.map(a, TinyColor.toHex8String)) === Some("#808080ff");
  });
});