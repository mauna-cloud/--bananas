module type Semigroup = {type t; let append: (t, t) => t;};
