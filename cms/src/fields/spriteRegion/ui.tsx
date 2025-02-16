import { useId } from 'react';

import { Grid, Flex } from '@keystar/ui/layout';
import { Text } from '@keystar/ui/typography';

import type {ObjectField, GenericPreviewProps, ComponentSchema} from '@keystatic/core'

const cellSize = 16;

export function SpriteRegionFieldInput<
  Fields extends Record<string, ComponentSchema>,
>({
  schema,
  fields,
}: GenericPreviewProps<ObjectField<Fields>, unknown>) {
  const id = useId();

  const labelId = `${id}-label`;
  const descriptionId = `${id}-description`;
  return (
    <Grid
      role="group"
      gap="medium"
      marginY="xlarge"
      aria-labelledby={labelId}
      aria-describedby={schema.description ? descriptionId : undefined}
    >
      <Text
        color="neutralEmphasis"
        size="medium"
        weight="semibold"
        id={labelId}
      >
        {schema.label}
      </Text>
      <Flex gap="xxlarge">

        <div>
          {Object.values(fields).map((field) => {
            const Input = field.schema.Input;
            return <Input {...field.schema} onChange={field.onChange} value={field.value} />
          })}
        </div>
        
        <div
          style={{
            width: cellSize * fields.width.value,
            height: cellSize * fields.height.value,
            transform:'scale(4)',
            transformOrigin: '0 0',
            backgroundSize: '16px 16px',
            backgroundImage: 'url(/public/grid.png)',
            imageRendering: 'pixelated',
          }}
        >
          <div
            style={{
              width: cellSize * fields.width.value,
              height: cellSize * fields.height.value,
              background: `url(/public/items.png) ${-fields.x.value * cellSize}px ${fields.y.value * cellSize}px`,
            }}
          />
        </div>
      </Flex>
    </Grid>
  );
}

