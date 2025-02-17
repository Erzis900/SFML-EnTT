import { defineConfig } from 'astro/config';
import react from '@astrojs/react';
import node from "@astrojs/node";
import keystatic from '@keystatic/astro';

// https://astro.build/config
export default defineConfig({
  integrations: [react(), keystatic()],
  output: "hybrid",
  adapter: node({
    mode: "standalone",
  }),
  
});
