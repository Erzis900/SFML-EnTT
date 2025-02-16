import { config, fields, collection, singleton } from '@keystatic/core';

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
      path: "src/content/database/items/*",
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
              label: 'Featured media',
              description: 'Optional image/video options for an optional hero media.',
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
                value: fields.relationship({
                  label: 'Value',
                  collection: 'attribute',
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
                defaultValue: 'Trigger',
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
                defaultValue: 'Set',
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
      },
    }),
    units: collection({
      label: "Units",
      slugField: 'id',
      path: "src/content/database/units/*",
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
        head: fields.relationship({
          label: 'Head',
          collection: 'items',
        }),
        chest: fields.relationship({
          label: 'Head',
          collection: 'items',
        }),
        cape: fields.relationship({
          label: 'Head',
          collection: 'items',
        }),
        mainShoulder: fields.relationship({
          label: 'Head',
          collection: 'items',
        }),
        offShoulder: fields.relationship({
          label: 'Head',
          collection: 'items',
        }),
        mainhand: fields.relationship({
          label: 'Head',
          collection: 'items',
        }),
        offhand: fields.relationship({
          label: 'Head',
          collection: 'items',
        }),
      }
    })
  },
  singletons: {
    settings: singleton({
      label: "Settings",
      path: "src/content/settings/settings",
      schema: {
        attribute: fields.array(
          fields.text({ label: "Attribute" }),
          {
            label: "Attribute",
            itemLabel: (props) => props.value,
          },
        ),
        scope: fields.array(
          fields.text({ label: "Scope" }),
          {
            label: "Scope",
            itemLabel: (props) => props.value,
          },
        ),
      },
    }),
  },
});
