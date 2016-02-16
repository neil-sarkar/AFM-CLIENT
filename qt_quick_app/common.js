requirejs.config({
    baseUrl: "qrc:/js",
    paths: {
        home: "pages/home",
        console: "console",
        jquery: 'lib/jquery',
        highcharts: 'lib/highcharts',
        react: 'lib/react',
        dom: 'lib/react-dom',
        browser: 'lib/browser',
        JSXTransformer: "JSXTransformer",
        jsx: "jsx",
    },
    jsx: {
        fileExtension: '.jsx'
    },
    name: "jsx!app",
});
