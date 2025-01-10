import { defineConfig } from 'astro/config';
import starlight from '@astrojs/starlight';

// https://astro.build/config
export default defineConfig({
  site: "https://doritothepug.github.io/Hamster",
  base: "Hamster",
	integrations: [
		starlight({
			title: 'Hamster',
			social: {
				github: 'https://github.com/DoritoThePug/Hamster',
			},
			sidebar: [
				{
					label: 'Start Here',
					items: [
						// Each item here is one entry in the navigation menu.
						{ label: 'Getting Started', link: 'start-here/getting-started'},
					],
				},
				{
					label: 'Reference',
					autogenerate: { directory: 'reference' },
				},
			],
		}),
	],
});
