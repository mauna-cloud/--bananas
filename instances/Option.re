/* Option.re */

open Typeclasses.Alternative;
open Typeclasses.Applicative;
open Typeclasses.Functor;
open Typeclasses.Monad;
open Typeclasses.Semigroup;
open Typeclasses.Traversable;

/* Option as Functor */
module OptionF_: Functor with type t('a) = option('a) = {
  type t('a) = option('a);
  let fmap = f =>
    fun
    | Some(x) => Some(f(x))
    | None => None;
};

module OptionFunctor = FunctorUtils(OptionF_);

/* Option as Applicative */
module OptionA_: Applicative with type t('a) = option('a) = {
  include OptionFunctor;
  let pure = x => Some(x);
  let ap = (f, x) =>
    switch (f, x) {
    | (Some(f), Some(x)) => Some(f(x))
    | _ => None
    };
};

module OptionApplicative = ApplicativeUtils(OptionA_);

/* Option as Alternative */
module OptionAl_: Alternative with type t('a) = option('a) = {
  include OptionApplicative;
  let empty = None;
  let (<|>) = (x, k) =>
    switch (x) {
    | None => k
    | x => x
    };
};

module OptionAlternative = AlternativeUtils(OptionAl_);

/* Option as Monad */
module OptionM_: Monad with type t('a) = option('a) = {
  include OptionApplicative;
  let bind = (m, f) =>
    switch (m) {
    | None => None
    | Some(x) => f(x)
    };
};

module OptionMonad = MonadUtils(OptionM_);

/* Option as Traversable */
module OptionTraversable =
       (A: Applicative)
       : (
           Traversable with
             type t('a) = option('a) and type Applicative.t('a) = A.t('a)
         ) => {
  type t('a) = option('a);
  module Applicative = A;
  module AppU = ApplicativeUtils(Applicative);
  open AppU;
  let traverse = (f, x) =>
    switch (x) {
    | None => A.pure(None)
    | Some(x) => (a => Some(a)) <$> f(x)
    };
};

// Generic type
module type GenericTypeConstuctor = {type t;};

/* Option as Semigroup */
module OptionSemigroup =
       (T: GenericTypeConstuctor)
       : (Semigroup with type t = option(T.t)) => {
  type t = option(T.t);
  let append = (m, n) =>
    switch (m) {
    | None => n
    | _ => m
    };
};
