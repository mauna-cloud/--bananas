module type Monad = {
  open Applicative;
  type t('a);
  include Applicative with type t('a) := t('a);
  let bind: (t('a), 'a => t('b)) => t('b);
};

module MonadUtils = (M: Monad) => {
  open Library.Util;
  include M;
  module AppU = Applicative.ApplicativeUtils(M);
  include (AppU :(module type of AppU) with type t('a) := AppU.t('a));
  
  let return = pure;
  let (>>=) = bind;
  let (=<<) = (f, m) => flip(bind, f, m);
  let join = m => id =<< m;
  let (>>) = (m, k) => m >>= const(k);
  let (<<) = (m,k) => flip((>>), m, k);
  let (>=>) = (f, g, x) => f(x) >>= g;
  let (<=<) = (f, g, x) => f =<< g(x);
};

module MonadLaws = (M: Monad) => {
  module MonadU = MonadUtils(M);
  open MonadU;
  let leftIdLaw = (f, x) => return(x) >>= f == f(x);
  let rightIdLaw = x => x >>= return == x;
  let associativityLaw = (m, f, g) =>
    m >>= (x => f(x) >>= g) == (m >>= f >>= g);
};
