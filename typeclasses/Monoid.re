module type Monoid = {
  type t;
  open Semigroup;
  include Semigroup with type t := t;
  let empty: t;
};

module MonoidUtils = (M: Monoid) => {
  include M;
  let (<+>) = (x, y) => append(x, y);
  let concat = xs => List.fold_left((<+>), empty, xs);
};
