(function (){
    var app = angular.module('store', []);

    app.controller('StoreController', function () {
        this.products = gems;
    });

    app.controller('PanelController', function () {
        this.tab = 1;
        this.selectTab = function (setTab) {
            this.tab = setTab;
        };
        this.isSelected = function (checkTab) {
            return this.tab === checkTab;
        };
    });

    var gems = [
        {
            name: 'Dodecahedron',
            price: 2.95,
            description: '...',
            canPurchase: false,
            images: [
                {
                    full: 'Dodecahedron-full.jpg',
                    thumb: 'Dodecahedron.jpg'
                }
            ]
        },
        {
            name: 'Pentagonal Gem',
            price: 5.95,
            description: '...',
            canPurchase: false,
            images: [
                {
                    full: 'Pentagonal-full.jpg',
                    thumb: 'Pentagonal.jpg'
                }
            ]
        }
    ]
})();

