open TestFramework;
open Bananas.Functor;

describe("List Functor", ({ test }) => {
  module ListFunctorLaws = FunctorLaws(ListFunctor);
  open ListFunctorLaws;

  test("Functor Laws", ({ expect }) => {
    expect.bool(idLaw([])).toBe(true);
    expect.bool(idLaw([1, 2])).toBe(true) |> ignore;

    let f = x => x mod 2;
    let g = x => x - 1;

    expect.bool(composeLaw(f, g, [])).toBe(true);
    expect.bool(composeLaw(f, g, [1, 2, 3])).toBe(true) |> ignore;
  });
});

describe("Option Functor", ({ test }) => {
  module OptionFunctorLaws = FunctorLaws(OptionFunctor);
  open OptionFunctorLaws;

  test("Functor Laws", ({ expect }) => {
    expect.bool(idLaw(None)).toBe(true);
    expect.bool(idLaw(Some(5))).toBe(true) |> ignore;

    let f = x => x mod 2;
    let g = x => x - 1;

    expect.bool(composeLaw(f, g, None)).toBe(true);
    expect.bool(composeLaw(f, g, Some(5))).toBe(true) |> ignore;
  });
});
