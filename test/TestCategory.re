open TestFramework;
open Bananas.Util;
open Bananas.Category;

describe("Function Category", ({ test }) => {
  open FunctionCategory;

  module FunctionSpecificLaws = {
    module FunctionCategoryLaws = CategoryLaws(FunctionCategory);
    include FunctionCategoryLaws;

    let rightIdLaw = (f, x) => call(f <<< id, x) == call(f, x);
    let leftIdLaw = (f, x) => call(id <<< f, x) == call(f, x);

    let composeLaw = (f, g, h, x) =>
      call((f <<< g) <<< h, 2) == call(f <<< (g <<< h), 2);
  }

  open FunctionSpecificLaws;

  test("Category Laws", ({ expect }) => {
    let f = x => x mod 2;
    let g = x => x - 1;
    let h = x => x + 9;

    expect.bool(rightIdLaw(Function(f), 2)).toBe(true);
    expect.bool(leftIdLaw(Function(f), 2)).toBe(true) |> ignore;

    expect.bool(composeLaw(
      Function(f), Function(g), Function(h), 6
    )).toBe(true) |> ignore;
  });
});
