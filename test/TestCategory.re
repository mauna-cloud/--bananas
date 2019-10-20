open TestFramework;
open Bananas.Typeclasses.Util;
open Bananas.Typeclasses.Category;

describe("Function Category", ({ test }) => {
  open FunctionCategory;

  module FunctionCategoryLaws = CategoryLaws(FunctionCategory);
  open FunctionCategoryLaws;

  test("Category Laws", ({ expect }) => {
    let f = x => x mod 2;
    let g = x => x - 1;
    let h = x => x + 9;

    let callWith2 = f => call(f, 2);

    expect.bool(rightIdLaw(
      Function(f),
      ~lift=callWith2, ()
    )).toBe(true);

    expect.bool(leftIdLaw(
      Function(f),
      ~lift=callWith2, ()
    )).toBe(true) |> ignore;

    expect.bool(composeLaw(
      Function(f), Function(g), Function(h),
      ~lift=callWith2, ()
    )).toBe(true) |> ignore;
  });
});
