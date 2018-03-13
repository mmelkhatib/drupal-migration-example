<?php

class USTravelEconomicFilesMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    // $this->dependencies = array('User');

    $source_fields = array(
      'fid' => t('Legacy Drupal 7 node id'),
    );
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'ustravel_migration') . '/includes/economic_impact_files.csv', $this->csvcolumns(), array('header_rows' => 1));
    $this->destination = new MigrateDestinationMedia('document');


    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'fid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'file_id',
          'alias' => 'f',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $format = MigrateTextFieldHandler::arguments(NULL, 'full_html', NULL);

    //$this->addFieldMapping('uid', 'post_author')->sourceMigration('User');
    $this->addFieldMapping('uid')->defaultValue(1);
    //$this->addFieldMapping('filename', 'filename');
   // $this->addFieldMapping('path')->defaultValue('sites/default/files/economic_impact');
    $this->addFieldMapping('destination_dir')->defaultValue('public://sites/default/files/economic_impact/states/current/');
    $this->addFieldMapping('destination_file', 'filename');
    //$this->addFieldMapping('timestamp', 'timestamp');

    $this->addFieldMapping('value', 'filename');
    $this->addFieldMapping('field_folder', 'media_folder');
    $this->addFieldMapping('pathauto')->defaultValue('TRUE');
    $this->addFieldMapping('source_dir')->defaultValue('/tmp/economic/');
    $this->addFieldMapping('file_replace')
      ->defaultValue(FILE_EXISTS_REPLACE);
  }

  function csvcolumns() {
    $columns[0] = array('fid', 'ID');
    $columns[1] = array('filename', 'filename');
    $columns[2] = array('title', 'title');
    $columns[3] = array('media_folder', 'media_folder');
    return $columns;
  }

  /**
   * Overload method for prepareRow().
   * @param $row
   * @return bool|void
   */
  public function prepareRow($row) {
    $test=1;
  }


}