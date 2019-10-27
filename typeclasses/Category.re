/* Category.re */

module type Category = {
  type t('a, 'b); 

  let id: t('a, 'a);
  let compose: t('b, 'c) => t('a, 'b) => t('a, 'c);
};

module CategoryUtils = (C: Category) => {
  open Library.Util;
  include C;
  
  let (<<<) = compose;
  let (>>>) = (f, g) => compose(g, f);
};

module CategoryLaws = (C: Category) => {
  include C;

  module CatU = CategoryUtils(C);
  open CatU;

  let rightIdLaw = (f, ~lift, ()) => lift(f <<< id) == lift(f);
  let leftIdLaw = (f, ~lift, ()) => lift(id <<< f) == lift(f);
  let composeLaw = (f, g, h, ~lift, ()) =>
    lift((f <<< g) <<< h) == lift(f <<< (g <<< h));
};
