/* Category.re */

module type Category = {
  type t('a, 'b); 

  let id: t('a, 'a);
  let compose: t('b, 'c) => t('a, 'b) => t('a, 'c);
};

module CategoryUtils = (C: Category) => {
  open Util;
  include C;
  
  let (<<<) = compose;
  let (>>>) = (f, g) => compose(g, f);
};

module CategoryLaws = (C: Category) => {
  open Util;
  include C;

  module CatU = CategoryUtils(C);
  open CatU;

  let rightIdLaw = f => (f <<< id) == f;
  let leftIdLaw = f => (id <<< f) == f;
  let composeLaw = (f, g, h) => ((f <<< g) <<< h) == (f <<< (g <<< h));
};

module FuncC_: Category with type t('a, 'b) = Util.func('a, 'b) = {
  open Util;
  type t('a, 'b) = func('a, 'b);

  let id = Function(x => x);
  let compose = (Function(f), Function(g)) => Function(f <<< g);
};

module FunctionCategory = CategoryUtils(FuncC_);
