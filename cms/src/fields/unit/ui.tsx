import { useId } from 'react';

import { Grid, Flex } from '@keystar/ui/layout';
import { Text } from '@keystar/ui/typography';

import type {ObjectField, GenericPreviewProps, ComponentSchema} from '@keystatic/core'
import { getCollection } from 'astro:content';

const items = await getCollection('items')
const itemsMap = Object.fromEntries(items.map(item => [item.id, item]))

const cellSize = 16;

const RenderItem = ({sprite, transform}) => (
  <div
    style={{
      position: 'absolute',
      width: cellSize * sprite.width,
      height: cellSize * sprite.height,
      background: `url(/public/items.png) ${-sprite.x * cellSize}px ${sprite.y * cellSize}px`,
      transform,
    }}
  />
)

export function UnitFieldInput<
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
        
        <div style={{padding: 50}}>
          <div style={{
            transformOrigin: '0 0',
            transform:'scale(4)',
            imageRendering: 'pixelated',
            position: 'relative'
          }}>
            <div
              style={{
                position: 'absolute',
                width: cellSize * 3,
                height: cellSize * 2,
                background: `url(/public/units.png) ${-fields.x.value * cellSize * 3}px ${fields.y.value * cellSize * 2}px`,
              }}
            />
            <RenderItem sprite={itemsMap[fields.head.value].data.sprite} transform={`translate(${cellSize / 2}px, 0px)`} />
            <RenderItem sprite={itemsMap[fields.chest.value].data.sprite} transform={`translate(${cellSize / 2}px, 0px)`} />
            <RenderItem sprite={itemsMap[fields.cape.value].data.sprite} transform={`translate(${cellSize / 2}px, 15px)`}  />
            <RenderItem sprite={itemsMap[fields.mainShoulder.value].data.sprite} transform={`translate(37px, 0)`}/>
            <RenderItem sprite={itemsMap[fields.offShoulder.value].data.sprite} transform={`translate(-4px, 0) scaleX(-1)`}/>
            <RenderItem sprite={itemsMap[fields.offhand.value].data.sprite} transform={`translate(-16px, -15px) rotate(-30deg)`} />
            <RenderItem sprite={itemsMap[fields.mainhand.value].data.sprite} transform={`translate(33px, -37px) rotate(-60deg)`} />
          </div>
        </div>
      </Flex>
    </Grid>
  );
}

