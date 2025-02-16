import { config, fields, collection } from '@keystatic/core';
import { getCollection } from 'astro:content';
import * as ANfields from './src/fields';

const items = await getCollection('items')
const itemsOptions = items.map(item => ({label: item.id === '0' ? 'None' : `${item.data.name}@${item.data.slot}`, value: item.id}))

const selectItems = ({label}: {label: string}) => fields.select({
  label,
  options: itemsOptions,
  defaultValue: '0'
})

export default config({
  storage: {
    kind: 'local',
  },
  collections: {
    scope: collection({
      label: 'Scope',
      slugField: 'scope',
      path: 'src/content/scope/*',
      schema: {
        scope: fields.slug({ name: { label: 'Scope' } }),
      },
    }),
    attribute: collection({
      label: 'Attribute',
      slugField: 'attribute',
      path: 'src/content/attribute/*',
      schema: {
        attribute: fields.slug({ name: { label: 'Attribute' } }),
      },
    }),
    slot: collection({
      label: 'Slot',
      slugField: 'slot',
      path: 'src/content/slot/*',
      schema: {
        slot: fields.slug({ name: {label: 'Slot'}})
      }
    }),
    trigger: collection({
      label: 'Trigger',
      slugField: 'trigger',
      path: 'src/content/trigger/*',
      schema: {
        trigger: fields.slug({ name: {label: 'Trigger'}})
      }
    }),
    items: collection({
      label: "Items",
      slugField: 'id',
      columns: ["name", "slot"],
      path: "src/content/items/*",
      format: "json",
      schema: {
        id: fields.text({
          label: 'Id',
          validation: {
            isRequired: true,
          }
        }),
        name: fields.text({
          label: 'Name',
          validation: {
            isRequired: true,
          }
        }),
        slot: fields.relationship({
          label: 'Slot',
          collection: 'slot',
          validation: {
            isRequired: true,
          }
        }),
        modifiers: fields.array({
          kind: 'conditional',
          discriminant: fields.select({
              label: 'Modifiers',
              options: [
                { label: 'Value', value: 'value' },
                { label: 'Trigger', value: 'trigger' },
              ],
              defaultValue: 'value',
            }),
          values: {
            value: fields.object({
                attribute: fields.relationship({
                  label: 'Attribute',
                  collection: 'attribute',
                  validation: {
                    isRequired: true,
                  }
                }),
                value: fields.number({
                  label: 'Value',
                  validation: {
                    isRequired: true,
                  }
                }),
                scope: fields.relationship({
                  label: 'Scope',
                  collection: 'scope',
                  validation: {
                    isRequired: true,
                  }
                }),
            }),
            trigger: fields.object({
              attribute: fields.text({
                label: 'Attribute',
                defaultValue: 'trigger',
                validation: {
                  isRequired: true,
                }
              }),
              value: fields.relationship({
                label: 'Value',
                collection: 'trigger',
                validation: {
                  isRequired: true,
                }
              }),
              scope: fields.text({
                label: 'Scope',
                defaultValue: 'set',
                validation: {
                  isRequired: true,
                }
              }),
            }),
          },
        }, 
        {
          label: 'Modifiers',
          itemLabel: props => `${props.value.fields.attribute.value}#${props.value.fields.scope.value} - ${props.value.fields.value.value}`
        }),
        sprite: ANfields.spriteRegion({
          x: fields.number({
            label: 'Position X',
            validation: {
              isRequired: true,
            }
          }),
          y: fields.number({
            label: 'Position Y',
            validation: {
              isRequired: true,
            }
          }),
          width: fields.number({
            label: 'Width',
            validation: {
              isRequired: true,
            }
          }),
          height: fields.number({
            label: 'Height',
            validation: {
              isRequired: true,
            }
          }),
        }),
      },
    }),
    units: collection({
      label: "Units",
      slugField: 'id',
      columns: ["name"],
      path: "src/content/units/*",
      format: "json",
      schema: {
        id: fields.text({
          label: 'Id',
          validation: {
            isRequired: true,
          }
        }),
        name: fields.text({
          label: 'Name',
          validation: {
            isRequired: true,
          }
        }),
        unit: ANfields.unit({
          x: fields.number({
            label: 'Position X',
            validation: {
              isRequired: true,
            }
          }),
          y: fields.number({
            label: 'Position Y',
            validation: {
              isRequired: true,
            }
          }),
          head: selectItems({
            label: 'Head',
          }),
          chest: selectItems({
            label: 'Chest',
          }),
          cape: selectItems({
            label: 'Cape',
          }),
          mainShoulder: selectItems({
            label: 'Main Shoulder',
          }),
          offShoulder: selectItems({
            label: 'Off Shoulder',
          }),
          mainhand: selectItems({
            label: 'Mainhand',
          }),
          offhand: selectItems({
            label: 'Offhand',
          }),
        })
      }
    })
  },
});
