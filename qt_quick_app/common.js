requirejs.config({
    baseUrl: "qrc:/js",
    paths: {
        home: "pages/home",
        console: "console",
        classnames: "lib/classNames",
        jquery: 'lib/jquery',
        highcharts: 'lib/highcharts',
        heatmap: 'lib/modules/heatmap',
        react: 'lib/react',
        dom: 'lib/react-dom',
        browser: 'lib/browser',
        JSXTransformer: "JSXTransformer",
        jsx: "jsx",
    },
    shim: {
    },
    jsx: {
        fileExtension: '.jsx'
    },
    name: "jsx!app",
});
