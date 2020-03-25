module type Applicative = {
  open Functor;
  type t('a);
  include Functor with type t('a) := t('a);
  let pure: 'a => t('a);
  let ap: (t('a => 'b), t('a)) => t('b);
};

module ApplicativeUtils = (A: Applicative) => {
  open Library.Util;
  include A;
  module FunU = Functor.FunctorUtils(A);
  include (FunU: (module type of FunU) with type t('a) := FunU.t('a));
  let (<*>) = f => ap(f);
  let liftA = (f, x) => f <$> x;
  let liftA2 = (f, x, y) => f <$> x <*> y;
  let liftA3 = (f, x, y, z) => f <$> x <*> y <*> z;
  let ( <* ) = (r, x) => const <$> r <*> x;
};

module ApplicativeLaws = (A: Applicative) => {
  open Library.Util;
  module AppU = ApplicativeUtils(A);
  open AppU;
  let idLaw = x => pure(id) <*> x == x;
  let homomorphismLaw = (f, x) => pure(f) <*> pure(x) == pure(f(x));
  let interchangeLaw = (u, y) => u <*> pure(y) == (pure(f => f(y)) <*> u);
  let compositionLaw = (u, v, w) =>
    pure((<<<)) <*> u <*> v <*> w == (u <*> (v <*> w));
};
