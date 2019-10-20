open Bananas.Typeclasses.Monoid;
open Bananas.Typeclasses.Semigroup;

/* String as Semigroup */
module StringSemigroup: Semigroup with type t = string = {
  type t = string;
  let append = (++);
};

/* String as Monoid */
module StringM_: Monoid with type t = string = {
  include Semigroup.StringSemigroup;
  let empty = "";
};

module StringMonoid = MonoidUtils(StringM_);