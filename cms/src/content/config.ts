// @ts-ignore
import { defineCollection, z } from 'astro:content';

const settings = defineCollection({
  type: "data",
  schema: z.object({
    title: z.string(),
    description: z.string().max(160),
    phone: z.string().min(9).max(9),
    email: z.string().email(),
    locations: z.array(z.string()),
  }),
});

export const collections = { settings };
