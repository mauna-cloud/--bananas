module Make = (M: Monad) => {
  open Library.Util;

  type m('a) = M.t;

  type t('i, 'o) =
    | Put('o, t('i, 'o))
    | Get('i => t('i, 'o))
    | Block(m(t('i, 'o)));

  module StreamProcCategory_: Category with type t('a, 'b) = t('i, 'o) = {
    let compose = (x, y) => {
      switch (x, y) {
      | (Get(sp2), Put(i, sp1)) => sp1 >>> sp2(i)
      | (Put(o, sp2), sp1) => Put(o, sp1 >>> sp2)
      | (Get(sp1), Get(sp2)) => Get(i => sp1(i) >>> Get(sp2))
      | (Block(spm), sp) => Block(fmap(x => sp >>> x, spm))
      | (sp, Block(spm)) => Block(fmap(x => x >>> sp, spm))
      };
    };
  };

  module StreamProcCategory = CategoryUtils(StreamProcCategory_);

  module Queue = {
    type queue('a) =
      | Queue(list('a), list('a));

    let make = () => {
      Queue([], []);
    };

    let push = (a, Queue(o, i)) => {
      Queue(o, [a, ...i]);
    };

    let rec pop = q => {
      switch (q) {
      | Queue([o, ...os], i) => Some(o, Queue(os, i))
      | Queue([], []) => None
      | Queue([], i) => pop(Queue(List.rev(i), []))
      };
    };
  };

  module StreamProcArrow_: Arrow with type t('a, 'b) = t('i, 'o) = {
    let rec arr = f => {
      Get(x => Put(f(x), arr(f)));
    };

    let rec bypass = (q, sp) => {
      switch (sp) {
      | Get(f) => Get((a, c) => bypass(Queue.push(c, q), f(a)))
      | Block(spm) => Block(fmap(bypass(q), spm))
      | Put(c, sp) =>
        switch (Queue.pop(q)) {
        | None => Get((_, d) => Put((c, d), bypass(q, sp)))
        | Some((c1, q1)) => Put((c, c1), bypass(q1, sp))
        }
      };
    };

    let first = x => bypass(Queue.make());
  };

  module StreamProcArrow = CategoryUtils(StreamProcArrow_);
};