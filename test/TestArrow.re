open TestFramework;
open Bananas.Util;
open Bananas.Arrow;

describe("Function Arrow", ({ test }) => {
  open FunctionArrow;

  module FunctionSpecificLaws = {
    module FunctionArrowLaws = ArrowLaws(FunctionArrow);
    include FunctionArrowLaws;

    let idLaw = x => call(arr(Bananas.Util.id), x) == call(id, x);

    let arrDistLaw = (f, g, x) =>
      call(arr(Bananas.Util.(f >>> g)), x) == call(arr(f) >>> arr(g), x);

    let firstFstLaw = (f, x) =>
      call(first(f) >>> arr(fst), x) == call(arr(fst) >>> f, x);

    let firstDistLaw = (f, g, x) =>
      call(first(f >>> g), x) == call(first(f) >>> first(g), x);

    let firstAssocLaw = (f, x) =>
      call(first(first(f)) >>> arr(assoc), x) == call(arr(assoc) >>> first(f), x);
  }

  open FunctionSpecificLaws;

  test("Arrow Laws", ({ expect }) => {
    let f = x => x mod 2;
    let g = x => x - 1;

    expect.bool(idLaw(2)).toBe(true);
    expect.bool(arrDistLaw(f, g, 2)).toBe(true);

    expect.bool(firstFstLaw(
      Function(f),
      (2, ())
    )).toBe(true) |> ignore;

    expect.bool(firstDistLaw(
      Function(f),
      Function(g),
      (2, ())
    )).toBe(true);

    expect.bool(firstAssocLaw(
      Function(f),
      ((2, ()), ())
    )).toBe(true) |> ignore;
  });
});
