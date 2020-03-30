/* Arrow.re */
/* http://hackage.haskell.org/package/base-4.12.0.0/docs/Control-Arrow.html */
module type ArrowZero = {
  open Arrow;
  type t('a, 'b);
  include Arrow with type t('a, 'b) := t('a, 'b);
  let zeroArrow: t('a, 'b);
};

module ArrowZeroUtils = (A: ArrowZero) => {
  include A;
  module ArrowU = Arrow.ArrowUtils(A);
  include (
    ArrowU: (module type of ArrowU) with type t('a, 'b) := ArrowU.t('a, 'b)
  );
};
