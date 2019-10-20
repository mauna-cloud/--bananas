open Arrow;
open Category;
open Util;
  
module FuncC_: Category with type t('a, 'b) = Util.func('a, 'b) = {
  open Util;
  type t('a, 'b) = func('a, 'b);

  let id = Function(Util.id);
  let compose = (Function(f), Function(g)) => Function(f <<< g);
};

module FunctionCategory = CategoryUtils(FuncC_);

module FuncA_: Arrow with type t('a, 'b) = Util.func('a, 'b) = {
  type t('a, 'b) = func('a, 'b);

  include (FuncC_:(module type of FuncC_) with type t('a, 'b) := t('a, 'b));

  let arr = f => Function(f);
  let first = (Function(f)) => Function(((x, y)) => (f(x), y));
};

module FunctionArrow = ArrowUtils(FuncA_);

Either (a => b) (exn => ())