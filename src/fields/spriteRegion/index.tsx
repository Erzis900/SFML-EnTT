import type { ComponentSchema, ObjectField, ObjectFieldOptions } from '@keystatic/core';
import { SpriteRegionFieldInput } from './ui';

export function spriteRegion<Fields extends Record<string, ComponentSchema>>(
  fields: Fields,
  opts?: ObjectFieldOptions
): ObjectField<Fields> {
  return { ...opts, kind: 'object', fields, Input: SpriteRegionFieldInput };
}
