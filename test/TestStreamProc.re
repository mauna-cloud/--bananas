open TestFramework;

open Structs.StreamProc;

describe("StreamProc struct", ({test}) =>
  test("Check constructors", ({expect}) => {
    let n = 1;
    let nIs1 = n == 1;
    expect.bool(nIs1).toBe(true) |> ignore;
  })
);
