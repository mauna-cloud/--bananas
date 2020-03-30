/* ArrowChoice.re */
/* http://hackage.haskell.org/package/base-4.12.0.0/docs/Control-Arrow.html */
module type ArrowChoice = {
  open Arrow;
  type t('a, 'b);
  include Arrow with type t('a, 'b) := t('a, 'b);
  let left: t('a, 'b) => t(result('a, 'd), result('b, 'd));
  let right: t('a, 'b) => t(result('d, 'a), result('d, 'b));
  let (+++):
    (t('a, 'b), t('aa, 'bb)) => t(result('a, 'aa), result('b, 'bb));
  let (|||): (t('a, 'c), t('b, 'c)) => t(result('a, 'b), 'c);
};

module ArrowChoiceUtils = (A: ArrowChoice) => {
  include A;
  module ArrowU = Arrow.ArrowUtils(A);
  include (
    ArrowU: (module type of ArrowU) with type t('a, 'b) := ArrowU.t('a, 'b)
  );
};
