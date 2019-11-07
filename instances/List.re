/* List.re */

open Typeclasses.Alternative;
open Typeclasses.Applicative;
open Typeclasses.Functor;
open Typeclasses.Monad;
open Typeclasses.Monoid;
open Typeclasses.Semigroup;
open Typeclasses.Traversable;
/* **
/* List as Functor */
module ListF_: Functor with type t('a) = list('a) = {
  type t('a) = list('a);
  let fmap = f => List.map(f);
};

module ListFunctor = FunctorUtils(ListF_);

/* List as Applicative */
module ListA_: Applicative with type t('a) = list('a) = {
  include ListFunctor;
  let pure = x => [x];
  let ap = (fs, xs) => fmap(f => fmap(x => f(x), xs), fs) |> List.concat;
};

module ListApplicative = ApplicativeUtils(ListA_);

/* List as Alternative */
module ListA_: Alternative with type t('a) = list('a) = {
  include ListApplicative;
  let empty = [];
  let (<|>) = (@);
};

module ListAlternative = AlternativeUtils(ListA_);

/* List as Monad */
module ListM_: Monad with type t('a) = list('a) = {
  include ListApplicative;
  let bind = (m, f) =>
    List.fold_right((x, y) => List.append(f(x), y), m, []);
};

module ListMonad = MonadUtils(ListM_);

// Generic type
module type GenericTypeConstuctor = {type t;};

/* List as Semigroup */
module ListSemigroup =
       (T: GenericTypeConstuctor)
       : (Semigroup with type t = list(T.t)) => {
  type t = list(T.t);
  let append = (@);
};

/* List as Monoid */
module ListM_ = (T: GenericTypeConstuctor) : (Monoid with type t = list(T.t)) => {
  include
    ListSemigroup(
      {
        type t = T.t;
      },
    );
  let empty = [];
};

module ListMonoid = (T: GenericTypeConstuctor) =>
  MonoidUtils(
    (
      ListM_(
        {
          type t = T.t;
        },
      )
    ),
  );

/* List as Traversable */  
module ListTraversable =
       (A: Applicative)
       : (
           Traversable with
             type t('a) = list('a) and type Applicative.t('a) = A.t('a)
         ) => {
  type t('a) = list('a);
  module Applicative = A;
  module AppU = ApplicativeUtils(Applicative);
  open AppU;
  let rec traverse = (f, xs) =>
    switch (xs) {
    | [] => A.pure([])
    | [x, ...xs] => ((y, ys) => [y, ...ys]) <$> f(x) <*> traverse(f, xs)
    };
};
** */
