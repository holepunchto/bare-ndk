const { test } = require('bare-tap')
const {
  AbsoluteSizeSpan,
  ForegroundColorSpan,
  LetterSpacingSpan,
  SpannableStringBuilder,
  Spanned,
  StrikethroughSpan,
  TextView,
  Typeface,
  TypefaceSpan,
  UnderlineSpan
} = require('..')
const text = require('../lib/text')

test('sets the text of a text view', (t) => {
  const view = new TextView()

  t.equal(view.text, '', 'empty')

  view.text = 'Grüße 👋'

  t.equal(view.text, 'Grüße 👋', 'round trips non-ASCII text')
})

test('sets the size and colour of the text', (t) => {
  const view = new TextView()

  t.ok(view.textSize > 0, 'has a default size')

  view.textSize = 30
  view.textColor = 0xff102030

  t.equal(view.textSize, 30, 'size')
  t.equal(view.textColor >>> 0, 0xff102030, 'colour')
})

test('sets how a text view lays out its text', (t) => {
  const view = new TextView()
  const { GRAVITY, JUSTIFICATION_MODE } = TextView

  t.equal(view.ellipsize, null, 'not ellipsized')

  view.gravity = GRAVITY.CENTER_HORIZONTAL | GRAVITY.BOTTOM
  view.justificationMode = JUSTIFICATION_MODE.INTER_WORD
  view.maxLines = 2
  view.ellipsize = 'END'

  t.equal(view.gravity, GRAVITY.CENTER_HORIZONTAL | GRAVITY.BOTTOM, 'gravity')
  t.equal(view.justificationMode, JUSTIFICATION_MODE.INTER_WORD, 'justification')
  t.equal(view.maxLines, 2, 'lines')
  t.equal(view.ellipsize, 'END', 'ellipsized')

  view.ellipsize = null

  t.equal(view.ellipsize, null, 'no longer ellipsized')
})

test('spaces the lines of a text view', (t) => {
  const view = new TextView()

  view.setLineSpacing(2, 1.5)

  t.equal(view.lineSpacingExtra, 2, 'extra')
  t.equal(view.lineSpacingMultiplier, 1.5, 'multiplier')

  view.lineHeight = 40

  t.equal(view.lineHeight, 40, 'line height')
})

test('keeps the typeface wrapper', (t) => {
  const view = new TextView()
  const typeface = Typeface.create('monospace', Typeface.STYLE.BOLD)

  t.ok(typeface !== null, 'created')

  view.typeface = typeface

  t.ok(view.typeface === typeface, 'same wrapper')
})

test('derives a typeface by weight', (t) => {
  const base = Typeface.create(null)
  const heavy = Typeface.create(base, 900, true)

  t.ok(heavy instanceof Typeface, 'a typeface')
  t.ok(heavy !== base, 'a new one')
})

test('builds styled text out of spans', (t) => {
  const view = new TextView()
  const builder = new SpannableStringBuilder()

  builder.append('Hello, ').append(new SpannableStringBuilder().append('world'))

  t.equal(builder.length, 12, 'length')

  const flags = Spanned.SPAN.EXCLUSIVE_EXCLUSIVE

  builder
    .setSpan(new AbsoluteSizeSpan({ size: 20, dip: true }), 0, 5, flags)
    .setSpan(new ForegroundColorSpan({ color: 0xffff0000 }), 0, 5, flags)
    .setSpan(new LetterSpacingSpan({ spacing: 2 }), 0, 5, flags)
    .setSpan(new StrikethroughSpan(), 7, 12, flags)
    .setSpan(new UnderlineSpan(), 7, 12, flags)
    .setSpan(new TypefaceSpan({ typeface: Typeface.create('serif') }), 7, 12, flags)

  view.text = builder

  t.equal(view.text, 'Hello, world', 'spans are not part of the text')
})

test('measures text', (t) => {
  const short = text.measure('Hello')
  const long = text.measure('Hello, world')

  t.ok(short.width > 0 && short.height > 0, 'has a size')
  t.equal(short.lines, 1, 'one line')
  t.ok(long.width > short.width, 'wider when longer')
  t.ok(text.measure('Hello, world', {}, long.width / 2).lines > 1, 'wraps')
  t.ok(text.measure('Hello', { size: 100 }).height > short.height, 'taller when larger')
  t.ok(
    text.measure('iiii', { family: 'monospace' }).width >
      text.measure('iiii', { family: 'serif' }).width,
    'in a family'
  )
})

test('measures styled text', (t) => {
  const plain = new SpannableStringBuilder().append('Hello')
  const large = new SpannableStringBuilder().append('Hello')

  large.setSpan(new AbsoluteSizeSpan({ size: 100 }), 0, 5, Spanned.SPAN.EXCLUSIVE_EXCLUSIVE)

  const small = text.measureSpanned(plain)

  t.equal(small.lines, 1, 'one line')
  t.ok(text.measureSpanned(large).height > small.height, 'taller with a larger span')
  t.ok(text.measureSpanned(large, small.width).lines > 1, 'wraps')

  const lines = new SpannableStringBuilder().append('Hello\nworld')

  // A line height spaces the lines apart, so the first keeps its own height.
  t.equal(
    text.measureSpanned(lines, Infinity, 200).height,
    small.height + 200,
    'with a line height'
  )
})
