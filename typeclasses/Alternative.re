module type Alternative = {
  type t('a);
  open Applicative;
  include Applicative with type t('a) := t('a);
  let empty: t('a);
  let (<|>): (t('a), t('a)) => t('a);
};

module AlternativeUtils = (A: Alternative) => {
  include A;
  module AppU = Applicative.ApplicativeUtils(A);
  include (AppU: (module type of AppU) with type t('a) := AppU.t('a));
  include Monoid;
  module AltMonoid =
         (T: GenericTypeConstuctor)
         : (Monoid with type t = A.t(T.t)) => {
    type t = A.t(T.t);
    let empty = A.empty;
    let append = A.(<|>);
  };
  let fail = empty;
  let choose = (type a, ps) => {
    module AM =
      MonoidUtils(
        (
          AltMonoid(
            {
              type t = a;
            },
          )
        ),
      );
    AM.concat(ps);
  };
};