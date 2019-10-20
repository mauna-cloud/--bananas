/* Result.re */

open Bananas.Typeclasses.Applicative;
open Bananas.Typeclasses.Functor;
open Bananas.Typeclasses.Monad;
open Bananas.Typeclasses.Semigroup;
open Bananas.Typeclasses.Traversable;

/* Result as Functor */
module ResultF_: Functor with type t('a) = result('a) = {
  type t('a) = result('a);
  let fmap = f =>
    fun
    | Ok(x) => Ok(f(x))
    | Error(e) => Error(e);
};

module ResultFunctor = FunctorUtils(ResultF_);

/* Result as Applicative */
module ResultA_: Applicative with type t('a) = result('a) = {
  include ResultFunctor;
  let pure = x => Ok(x);
  let ap = (f, x) =>
    switch (f, x) {
    | (Error(e), _) => Error(e)
    | (Ok(f), r) => fmap(f, r)
    };
};

module ResultApplicative = ApplicativeUtils(ResultA_);

/* Result as Monad */
module ResultM_: Monad with type t('a) = result('a) = {
  include ResultApplicative;
  let bind = (m, f) =>
    switch (m) {
    | Error(e) => Error(e)
    | Ok(x) => f(x)
    };
};

module ResultMonad = MonadUtils(ResultM_);

/* Result as Traversable */
module ResultTraversable =
       (A: Applicative)
       : (
           Traversable with
             type t('a) = result('a) and type Applicative.t('a) = A.t('a)
         ) => {
  type t('a) = result('a);
  module Applicative = A;
  module AppU = ApplicativeUtils(Applicative);
  open AppU;
  let traverse = (f, x) =>
    switch (x) {
    | Error(e) => A.pure(e)
    | Ok(x) => (a => Ok(a)) <$> f(x)
    };
};

// Generic type
module type GenericTypeConstuctor = {type t;};

/* Result as Semigroup */
module ResultSemigroup =
       (T: GenericTypeConstuctor)
       : (Semigroup with type t = result(T.t)) => {
  type t = result(T.t);
  let append = (m, n) =>
    switch (m) {
    | Error(_) => n
    | _ => m
    };
};
