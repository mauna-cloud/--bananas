open TestFramework;
open Bananas.Typeclasses.Util;
open Bananas.Typeclasses.Arrow;

describe("Function Arrow", ({ test }) => {
  open FunctionArrow;

  module FunctionArrowLaws = ArrowLaws(FunctionArrow);
  open FunctionArrowLaws;

  test("Arrow Laws", ({ expect }) => {
    let f = x => x mod 2;
    let g = x => x - 1;

    let callWith2 = x => call(x, 2);
    let callWithP2 = x => call(x, (2, ()));
    let callWithP_P2 = x => call(x, ((2, ()), ()));

    expect.bool(idLaw(
      ~lift=callWith2, ()
    )).toBe(true);

    expect.bool(arrDistLaw(
      f, g,
      ~lift=callWith2, ()
    )).toBe(true);

    expect.bool(firstFstLaw(
      Function(f),
      ~lift=callWithP2, ()
    )).toBe(true) |> ignore;

    expect.bool(firstDistLaw(
      Function(f),
      Function(g),
      ~lift=callWithP2, ()
    )).toBe(true);

    expect.bool(firstAssocLaw(
      Function(f),
      ~lift=callWithP_P2, ()
    )).toBe(true) |> ignore;
  });
});
