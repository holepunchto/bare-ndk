import EventEmitter from 'bare-events'
import { tag, handle, Handle } from 'bare-jni-registry'

/**
 * The base of every Android object in this module. Objects that have events emit them as
 * ordinary events, and Android is only asked to report an event while something listens to it.
 * Lengths are in physical pixels and colours are ARGB numbers, such as `0xff0000ff` for blue.
 */
interface NDKObject<M extends Record<keyof M, unknown[]> = {}> extends EventEmitter<M> {
  readonly [tag]: number

  readonly [handle]: Handle
}

declare class NDKObject<M extends Record<keyof M, unknown[]> = {}> {
  protected constructor()
}

export = NDKObject
