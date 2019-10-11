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
  open Util;
  include A;

  module CatU = Category.CategoryUtils(A);
  include (
    CatU:(module type of CatU)
      with type t('a, 'b) := CatU.t('a, 'b)
  );

  let (***) = (f, g) => first(f) >>> arr(swap) >>> first(g) >>> arr(swap);

  let second = a => a *** id;
  let (&&&) = (f, g) => arr (b => (b, b)) >>> f *** g;
};

module ArrowLaws = (A: Arrow) => {
  open Util;
  include A;

  module ArrU = ArrowUtils(A);
  open ArrU;

  let idLaw = x => arr(Util.id) == id;
  let arrDistLaw = (f, g) => arr(Util.(f >>> g)) == (arr(f) >>> arr(g));

  let firstFstLaw = f => (first(f) >>> arr(fst)) == (arr(fst) >>> f);
  let firstDistLaw = (fa, ga) => first(fa >>> ga) == (first(fa) >>> first(ga));

  let firstAssocLaw = (f: t('a, 'b)) =>
    first(first(f)) >>> arr(assoc) == (arr(assoc) >>> first(f));
};

module FuncA_: Arrow with type t('a, 'b) = Util.func('a, 'b) = {
  open Util;
  open Category;
  type t('a, 'b) = func('a, 'b);

  include (FuncC_:(module type of FuncC_) with type t('a, 'b) := t('a, 'b));

  let arr = f => Function(f);
  let first = (Function(f)) => Function(((x, y)) => (f(x), y));
};

module FunctionArrow = ArrowUtils(FuncA_);
