<?php // vim: et
/* The format is:
 * array(
 *     "major release number" => array(
 *         "release" => array(
 *             "source/windows" => array(
 *                 "filename" => "filename.tar.bz2",
 *                 "name"     => "package name",
 *                 "sha256"   => "shasum -256",
 *                 "date"     => "this files release date",
 *                 "note"     => "this file was updated 29feb due to broken phar files..",
 *             ),
 *             "announcement" => "bool, release announcement exists in releases/?",
 *         ),
 *     ),
 * );
 */
$RELEASES = (function() {
    $data = [];

    /* PHP 8.1 Release */
    $data['8.1'] = [
        'version' => '8.1.2',
        'date'    => '20 Jan 2021',
        'tags'    => [], // Set to ['security'] for security releases.
        'sha256' => [
            'tar.gz'  => '9992409c0543e0c8e89914f7307e1485a08c057091146e4731565b59065f8bde',
            'tar.bz2' => '913dc7dd4388427fa33ea4ac89834e856ff5394f4218eace260a3a279f5b53a9',
            'tar.xz'  => '6b448242fd360c1a9f265b7263abf3da25d28f2b2b0f5465533b69be51a391dd',
        ]
    ];

    /* PHP 8.0 Release */
    $data['8.0'] = [
        'version' => '8.0.15',
        'date'    => '20 Jan 2022',
        'tags'    => [], // Set to ['security'] for security releases.
        'sha256' => [
            'tar.gz'  => '47f0be6188b05390bb457eb1968ea19463acada79650afc35ec763348d5c2370',
            'tar.bz2' => '881171c90aba746d28df768f3d99fa3261999e506415be4c7352078a64fe59dc',
            'tar.xz'  => '5f33544061d37d805a2a9ce791f081ef08a7155bd7ba2362e69bba2d06b0f8b2',
        ]
    ];

    /* PHP 7.4 Release */
    $data['7.4'] = [
        'version' => '7.4.27',
        'date'    => '16 Dec 2021',
        'tags'    => [], // Set to ['security'] for security releases
        'sha256'  => [
            'tar.gz'  => '564fd5bc9850370db0cb4058d9087f2f40177fa4921ce698a375416db9ab43ca',
            'tar.bz2' => '184aaef313fbf28c9987f6aa07b655cd1b0eae9e7e17061775a3e7d880185563',
            'tar.xz'  => '3f8b937310f155822752229c2c2feb8cc2621e25a728e7b94d0d74c128c43d0c',
        ]
    ];

    $ret = [];
    foreach ($data as $release) {
        $version = $release['version'];
        [$major] = explode('.', $version, 2);

        $info = [
            'announcement' => $release['announcement'] ?? true,
            'tags' => $release['tags'],
            'date' => $release['date'],
            'source' => [],
        ];
        foreach ($release['sha256'] as $format => $hash) {
            $info['source'][] = [
                'filename' => "php-{$version}.{$format}",
                'name' => "PHP {$version} ({$format})",
                'sha256' => $hash,
                'date' => $release['date'],
            ];
        }
        $ret[$major][$version] = $info;
    }
    return $ret;
})();

// Get latest release version and info.
function release_get_latest() {
    global $RELEASES;

    $version = null;
    $current = null;
    foreach ($RELEASES as $versions) {
        foreach ($versions as $ver => $info) {
            if (version_compare($ver, $version) > 0) {
                $version = $ver;
                $current = $info;
            }
        }
    }

    return [ $version, $current ];
}
