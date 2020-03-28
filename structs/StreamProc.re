/* StreamProc.re */
module type StreamProc = {
  type m('a);
  type t('i, 'o) =
    | Get('i => t('i, 'o))
    | Put('o, t('i, 'o))
    | Block(m(t('i, 'o)));
};
