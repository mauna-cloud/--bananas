/* 
  identity function
  id :: a -> a
 */
let id = (x) => x;

/* 
  dollar function
  ($) :: (a -> b) -> a -> b
 */
let ($) = (f,x) => f(x);

/* 
  flip function
  flip :: (a -> b -> c) -> b -> a -> c
 */
let flip = (f,x,y) => f(y,x);

/* 
  const function
  const :: a -> b -> a
 */
let const = (x,_) => x;

/* 
  compose function
  (<<<) :: (b -> c) -> (a -> b) -> a -> c
 */
let compose = (f, g, x) => f(g(x));
let (<<<) = compose;

/* 
  flip compose function
  (>>>) :: (a -> b) -> (b -> c) -> a -> c
 */
let flip_compose = (f, g, x) => g(f(x));
let (>>>) = flip_compose;

/* 
  swap function
  swap :: ((a, b)) -> (b, a)
 */
let swap = p => (snd(p), fst(p));

/* 
  assoc function
  assoc :: (((a, b), c)) -> (a, (b, c))
 */
let assoc = ((p, c)) => (fst(p), (snd(p), c));

