open Typeclasses.Monad;
open Typeclasses.Category;
open Typeclasses.Arrow;
// open Instances.Option;

module type StreamProc = {
  type m('a);
  type t('i, 'o) =
    | Get('i => t('i, 'o))
    | Put('o, t('i, 'o))
    | Block(m(t('i, 'o)));
};

module type GenericTypeConstuctor = {type t('a, 'b);};
//(StreamProc with type m('a) = M.t('a) and type t('i, 'o) = T.t('i, 'o))

module MakeStream = (M: Monad, T: GenericTypeConstuctor) => {
  type m('a) = M.t('a);
  type t('i, 'o) =
    | Get('i => t('i, 'o))
    | Put('o, t('i, 'o))
    | Block(m(t('i, 'o)));
};

module Cake = MakeStream(Option.OptionMonad);
module CakeF = Cake(Function.FunctionCategory);

module Cake_: Category with type t('a, 'b) = Function.func('a, 'b) = {
  include CakeF;
  // let fmap_ = Option.OptionMonad.fmap;
  let fmap_ = f =>
    fun
    | Some(x) => Some(f(x))
    | None => None;

  let rec id = Get(x => Put(x, id));
  let rec compose = (x, y) => {
    switch (x, y) {
    | (Get(sp2), Put(i, sp1)) => sp1 >>> sp2(i)
    | (Put(o, sp2), sp1) => Put(o, sp1 >>> sp2)
    | (Get(sp1), Get(sp2)) => Get(i => sp1(i) >>> Get(sp2))
    | (Block(spm), sp) => Block(fmap_(x => sp >>> x, spm))
    | (sp, Block(spm)) => Block(fmap_(x => x >>> sp, spm))
    };
  }
  and (>>>) = (f, g) => compose(g, f);
};

// module Packet: Monad with type t('a) = option('a) = {
//   include Option.OptionMonad;

// }

// module PacketTransformer = (M: Monad) => {

// }

// module PacketTransformer: StreamProc with type m('a) = Packet.t('a) = {
//   type m('a) = Packet.t('a);
//   type t('i, 'o) =
// }

// module type MakeMType = (M: Monad) => {
//   type m('a);
// };

// module MakeM: MakeMType = (M: Monad) => {
//   type m('a) = M.t('a);
// };

// module OptionM = MakeM(Option.OptionMonad);

// module FuncA_: Arrow with type t('a, 'b) = func('a, 'b) = {
//   type t('a, 'b) = func('a, 'b);

//   include (FuncC_:(module type of FuncC_) with type t('a, 'b) := t('a, 'b));

//   let arr = f => Function(f);
//   let first = (Function(f)) => Function(((x, y)) => (f(x), y));
// };

// module FunctionArrow = ArrowUtils(FuncA_);

// module StreamA_: Arrow with type t('a, 'b) = StreamProc.t('a, 'b) = {

// }

module Make = (A: Arrow) => {
  // open Library.Util;

  // type m('a) = M.t('a);
  // type t('i, 'o) =
  //   | Get('i => A.t('i, 'o))
  //   | Put('o, A.t('i, 'o))
  //   | Block(m(A.t('i, 'o)));

  // type streamProc('i, 'o) =
  //   | Put('o, streamProc('i, 'o))
  //   | Get('i => streamProc('i, 'o))
  //   | Block(m(streamProc('i, 'o)));

  // module StreamProcCategory_: Category with type t('a, 'b) = streamProc('a, 'b) = {
  //   open Library.Util;

  //   type t('a, 'b) = streamProc('a, 'b);
  //   let rec id = Get(x => Put(x, id));

  //   let compose = (x, y) => {
  //     switch (x, y) {
  //     | (Get(sp2), Put(i, sp1)) => sp1 >>> sp2(i)
  //     | (Put(o, sp2), sp1) => Put(o, sp1 >>> sp2)
  //     | (Get(sp1), Get(sp2)) => Get(i => sp1(i) >>> Get(sp2))
  //     | (Block(spm), sp) => Block(fmap(x => sp >>> x, spm))
  //     | (sp, Block(spm)) => Block(fmap(x => x >>> sp, spm))
  //     };
  //   };
  // };

  // module StreamProcCategory = CategoryUtils(StreamProcCategory_);

  module Queue = {
    type queue('a) =
      | Queue(list('a), list('a));

    let make = () => {
      Queue([], []);
    };

    let push = (a, Queue(o, i)) => {
      Queue(o, [a, ...i]);
    };

    let rec listRev = lst => {
      switch (lst) {
      | [] => []
      | [x, ...xs] => listRev(xs) @ [x]
      };
    };

    let rec pop = q => {
      switch (q) {
      | Queue([o, ...os], i) => Some((o, Queue(os, i)))
      | Queue([], []) => None
      | Queue([], i) => pop(Queue(listRev(i), []))
      };
    };
  };
  // module StreamProcArrow_: Arrow with type t('a, 'b) = streamProc('a, 'b) = {
  //   let rec arr = f => {
  //     Get(x => Put(f(x), arr(f)));
  //   };
  //   let rec bypass = (q, sp) => {
  //     switch (sp) {
  //     | Get(f) => Get(((a, c)) => bypass(Queue.push(c, q), f(a)))
  //     | Block(spm) => Block(fmap(bypass(q), spm))
  //     | Put(c, sp) =>
  //       switch (Queue.pop(q)) {
  //       | None => Get(((_, d)) => Put((c, d), bypass(q, sp)))
  //       | Some((c1, q1)) => Put((c, c1), bypass(q1, sp))
  //       }
  //     };
  //   };
  //   let first = x => bypass(Queue.make());
  // };
  // module StreamProcArrow = ArrowUtils(StreamProcArrow_);
};