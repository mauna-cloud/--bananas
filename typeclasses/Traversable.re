open Applicative;

module type Traversable = {
  type t('a);
  module Applicative: Applicative;
  let traverse: ('a => Applicative.t('b), t('a)) => Applicative.t(t('b));
};
