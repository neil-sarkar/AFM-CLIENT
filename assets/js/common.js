requirejs.config({
    baseUrl: "js",
    paths: {
        home: "pages/home",
        jquery: 'lib/jquery',
        highcharts: 'lib/highcharts',
        handlebars: 'lib/handlebars',
        react: 'lib/react',
        dom: 'lib/react-dom',
        browser: 'lib/browser',
        JSXTransformer: "JSXTransformer",
        jsx: "jsx",
        synced_chart: 'components/synced_chart',
    },
    jsx: {
        fileExtension: '.jsx'
    },
    name: "jsx!app",
});


