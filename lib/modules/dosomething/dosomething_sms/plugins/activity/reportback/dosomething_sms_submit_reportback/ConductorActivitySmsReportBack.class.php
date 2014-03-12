<?php

/**
 * Submit report back with data received through a ConductorWorkflow.
 */
class ConductorActivitySmsReportBack extends ConductorActivity {

  /**
   * Context in which the submitted MMS URL can be found.
   *
   * @var string
   */
  public $mmsContext;

  /**
   * Node ID to submit the report back to.
   *
   * @var int
   */
  public $nid;

  /**
   * Maps report back submission properties to the context names their values
   * should be pulled from.
   *
   * @var array
   */
  public $propertyToContextMap;

  /**
   * Mobile Commons opt-in path ID to send user to after submission.
   *
   * @var int
   */
  public $optInPathId;

  /**
   * Mobile Commons campaign ID to opt the user out of after submission.
   *
   * @var int
   */
  public $optOutCampaignId;

  /**
   * The Mobile Commons campaign Id that $this->optInPathId resides in. This
   * helps on the Mobile Commons end to determine if this report back is the
   * first campaign completed on SMS by this user.
   *
   * @var int
   */
  public $mobileCommonsCompletedCampaignId;

  /**
   * Called when this activity gets activated and run by the containing
   * ConductorWorkflow's controller.
   */
  public function run() {
    $state = $this->getState();
    $mobile = $state->getContext('sms_number');

    // Mobile Commons sends the international code in its payload. Remove it.
    $mobile = substr($mobile, -10);

    // Get user by mobile number if it exists. Otherwise create it.
    $user = dosomething_user_get_user_by_mobile($mobile);
    if (!$user) {
      $user = dosomething_user_create_user_by_mobile($mobile);
    }

    // Initialize reportback values, defaulting to create a new reportback.
    $values = array(
      'rbid' => 0,
    );

    // Check for a previously submitted reportback to update instead.
    if ($rbid = dosomething_reportback_exists($this->nid, $user->uid)) {
      $values['rbid'] = $rbid;
    }

    // Get the MMS URL from the provided context.
    $pictureUrl = $state->getContext($this->mmsContext);

    // Download, save, and move the file to proper directory.
    $pictureContents = file_get_contents($pictureUrl);
    $file = file_save_data($pictureContents, $pictureFilename);
    $new_dest = dosomething_reportback_get_file_dest($file->name, $this->nid, $user->uid);
    $file = file_move($file, $new_dest);

    // Save UID and permanent status.
    $file->uid = $user->uid;
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);

    // Get the fid to submit with the report back.
    $values['fid'] = $file->fid;

    // Get answers from context and set them to their appropriate properties.
    foreach ($this->propertyToContextMap as $property => $context) {
      $values[$property] = $state->getContext($context);
    }

    // Set nid and uid.
    $values['nid'] = $this->nid;
    $values['uid'] = $user->uid;

    // Create/update a report back submission.
    $rbid = dosomething_reportback_save($values);

    // Update user's profile if this is the first completed campaign.
    $updateArgs = array();
    if (empty($_REQUEST['profile_first_completed_campaign_id']) && !empty($this->mobileCommonsCompletedCampaignId)) {
      $updateArgs['person[first_completed_campaign_id]'] = $this->mobileCommonsCompletedCampaignId;
    }

    // Opt the user out of the main campaign.
    if (!empty($this->optOutCampaignId)) {
      dosomething_sms_mobilecommons_opt_out($mobile, $this->optOutCampaignId);
    }

    // Opt user into a path to send the confirmation message.
    dosomething_sms_mobilecommons_opt_in($mobile, $this->optInPathId, $updateArgs);

    $state->setContext('ignore_no_response_error', TRUE);
    $state->markCompleted();
  }
}
