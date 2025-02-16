import type { ComponentSchema, ObjectField, ObjectFieldOptions } from '@keystatic/core';
import { UnitFieldInput } from './ui';

export function unit<Fields extends Record<string, ComponentSchema>>(
  fields: Fields,
  opts?: ObjectFieldOptions
): ObjectField<Fields> {
  return { ...opts, kind: 'object', fields, Input: UnitFieldInput };
}
