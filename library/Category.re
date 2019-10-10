module type Category = {
  type t('a, 'b); 

  let id: ('a) => t('a, 'a);
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

  let rightIdLaw = (f, x) => (f <<< id(x)) == f;
  let leftIdLaw = (f, x) => (id(x) <<< f) == f;
  let composeLaw = (f, g, h) => ((f <<< g) <<< h) == (f <<< (g <<< h));
};

type func('a, 'b) = Function('a => 'b);
let call = (Function(f), a) => f(a);

module FuncC_: Category with type t('a, 'b) = func('a, 'b) = {
  type t('a, 'b) = func('a, 'b);
  open Util;

  let id = x => Function(_ => x);
  let compose = (Function(f), Function(g)) => Function(g >>> f);
};

module FunctionCategory = CategoryUtils(FuncC_);
