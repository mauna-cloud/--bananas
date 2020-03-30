/* Arrow.re */
/* http://hackage.haskell.org/package/base-4.12.0.0/docs/Control-Arrow.html */
module type ArrowLoop = {
  open Arrow;
  type t('a, 'b);
  include Arrow with type t('a, 'b) := t('a, 'b);
  let loop: t(('b, 'a), ('c, 'a)) => t('b, 'c);
};

module ArrowLoopUtils = (A: ArrowLoop) => {
  include A;
  module ArrowU = Arrow.ArrowUtils(A);
  include (
    ArrowU: (module type of ArrowU) with type t('a, 'b) := A.t('a, 'b)
  );
};

module ArrowLoopLaws = (A: ArrowLoop) => {
  open Library.Util;
  include A;
  module ArrLoopU = ArrowLoopUtils(A);
  open ArrLoopU;
  /* --------- */
  /* law utils */
  /*
     let assoc = ((a, b), c) => (a, (b, c));
     let unassoc = (a, (b, c)) => ((a, b), c);
     let rec fix = f => f(fix(f));
     /* extension */
     let extensionLaw = f =>
       loop(arr(f)) == arr(b => fst(fix(((c, d)) => f(b, d))));
     /* left tightening */
     let leftTightening = (f, h) => loop(first(h >>> f)) == h >>> loop(f);
     /* right tightening */
     let rightTightening = (f, h) => loop(f >>> first(h)) == loop(f) >>> h;
     /* sliding */
     let sliding = (f, k) =>
       loop(f >>> arr(id *** k)) == loop(arr(id *** k) >>> f);
     /* vanishing */
     let vanishing = f =>
       loop(loop(f)) == loop(arr(unassoc) >>> f >>> arr(assoc));
     /* superposing */
     let superposing = f =>
       second(loop(f)) == loop(arr(assoc) >>> second(f) >>> arr(unassoc));
   */
};
