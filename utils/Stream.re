/* Stream.re */

/**

open Base;

let calcOffset:
    (Stream.t('a), Stream.t('b)) => int
  = (st_a, st_b) => Stream.count(st_a) - Stream.count(st_b);

let map:
    ('a => 'b, Stream.t('a)) => Stream.t('b)
  = (fn, stream) => {
  let initialCount = Stream.count(stream);

  let result = Stream.from(
    n => {
    let adjusted: int = initialCount + n;
    let peeked: list('a) = Stream.npeek(adjusted, stream);

    let result = switch(List.hd(List.rev(peeked))) {
    | Some(x) => Some(fn(x))
    | None => None
    | exception Failure(_) => None
    };

    result;
  });

  result;
};

**/
