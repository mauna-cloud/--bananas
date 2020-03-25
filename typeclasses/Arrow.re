/* Arrow.re */
/* http://hackage.haskell.org/package/base-4.12.0.0/docs/Control-Arrow.html */
module type Arrow = {
  open Category;
  type t('a, 'b);
  include Category with type t('a, 'b) := t('a, 'b);
  let arr: ('a => 'b) => t('a, 'b);
  let first: t('a, 'b) => t(('a, 'd), ('b, 'd));
};

module ArrowUtils = (A: Arrow) => {
  open Library.Util;
  include A;
  module CatU = Category.CategoryUtils(A);
  include (
    CatU: (module type of CatU) with type t('a, 'b) := CatU.t('a, 'b)
  );
  let ( *** ) = (f, g) =>
    first(f) >>> arr(swap) >>> first(g) >>> arr(swap);
  let second = a => a *** id;
  let (&&&) = (f, g) => arr(b => (b, b)) >>> f *** g;
};

module ArrowLaws = (A: Arrow) => {
  open Library.Util;
  include A;
  module ArrU = ArrowUtils(A);
  open ArrU;
  let idLaw = (~lift, ()) => lift(arr(Library.Util.id)) == lift(id);
  let arrDistLaw = (f, g, ~lift, ()) =>
    lift(arr(Library.Util.(f >>> g))) == lift(arr(f) >>> arr(g));
  let firstFstLaw = (f, ~lift, ()) =>
    lift(first(f) >>> arr(fst)) == lift(arr(fst) >>> f);
  let firstDistLaw = (fa, ga, ~lift, ()) =>
    lift(first(fa >>> ga)) == lift(first(fa) >>> first(ga));
  let firstAssocLaw = (f: t('a, 'b), ~lift, ()) =>
    lift(first(first(f)) >>> arr(assoc))
    == lift(arr(assoc) >>> first(f));
};
