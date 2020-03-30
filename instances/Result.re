/* Result.re */

open Typeclasses.Applicative;
open Typeclasses.Functor;
open Typeclasses.Monad;
open Typeclasses.Semigroup;
open Typeclasses.Traversable;

/* Result type */
type result('a, 'b) =
  | Ok('a)
  | Error('b);

/* Result as Functor */
module ResultF_: Functor with type t('a) = result('a, exn) = {
  type t('a) = result('a, exn);
  let (===) = Base.(===);

  let fmap = f =>
    fun
    | Ok(x) => Ok(f(x))
    | Error(e) => Error(e);
};

module ResultFunctor = FunctorUtils(ResultF_);

/* Result as Applicative */
module ResultA_: Applicative with type t('a) = result('a, exn) = {
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
module ResultM_: Monad with type t('a) = result('a, exn) = {
  include ResultApplicative;
  let bind = (m, f) =>
    switch (m) {
    | Error(e) => Error(e)
    | Ok(x) => f(x)
    };
};

module ResultMonad = MonadUtils(ResultM_);

/* Result as Traversable */
/*
module ResultTraversable =
       (A: Applicative)
       : (
           Traversable with
             type t('a) = result('a, exn) and type Applicative.t('a) = A.t('a)
         ) => {
  type t('a) = result('a, exn);
  module Applicative = A;
  module AppU = ApplicativeUtils(Applicative);
  open AppU;
  let traverse = (f, x) =>
    switch (x) {
    | Error(e) => A.pure(e)
    | Ok(x) => (a => Ok(a)) <$> f(x)
    };
};
*/

// Generic type
module type GenericTypeConstuctor = {type t;};

/* Result as Semigroup */
module ResultSemigroup =
       (T: GenericTypeConstuctor)
       : (Semigroup with type t = result(T.t, exn)) => {
  type t = result(T.t, exn);
  let append = (m, n) =>
    switch (m) {
    | Error(_) => n
    | _ => m
    };
};
