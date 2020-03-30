/* Arrow.re */
/* http://hackage.haskell.org/package/base-4.12.0.0/docs/Control-Arrow.html */
module type ArrowPlus = {
  type t('a, 'b);
  open ArrowZero;
  include ArrowZero with type t('a, 'b) := t('a, 'b);
  let (<+>): (t('a, 'b), t('a, 'b)) => t('a, 'b);
};

module ArrowPlusUtils = (A: ArrowPlus) => {
  include A;
  module ArrowZeroU = ArrowZero.ArrowZeroUtils(A);
  include (
    ArrowZeroU:
      (module type of ArrowZeroU) with type t('a, 'b) := ArrowZeroU.t('a, 'b)
  );
};
